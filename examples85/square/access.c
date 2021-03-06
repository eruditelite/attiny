/*
  access.c

  Access to target registers using pigpio via socket interface.

  Each project can define "registers" that can be accessed via i2c.
  Each register will have the following:

  1) A name.
  2) An offset from 0...255.
  3) A width.
  4) An access property, read only or read write.

  Bit 7 is the read/write bit in the command, bits 6:0 are the offset.

  All projects should have the following.

  magic, 0x00, 2, ro
  project, 0x01, 2, ro
  version, 0x02, 2, ro

  In this case, three writable registers are added, dummy1, dummy2,
  and dummy4 (char, short, and long).
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <limits.h>
#include <pigpiod_if2.h>

/*
  Options, Addresses, Etc.
*/

static int speed = 20000;
static int pi = -1;
static int verbose = 0;

static int sda = 2;
static int scl = 3;
static int i2c_address = 5;

struct tr {
	const char *name;
	int offset;
	int width;
	int ro;
};

enum trname {
	trmagic = 0,
	trproject = 1,
	trversion = 2,
	trpllcsr = 3,
	trtccr1 = 4,
	trocr1a = 5
};

struct tr trs[] = {
	{"magic",   trmagic, 2, 1},
	{"project", trproject, 2, 1},
	{"version", trversion, 2, 1},
	{"pllcsr", trpllcsr, 1, 0},
	{"tccr1", trtccr1, 1, 0},
	{"ocr1a", trocr1a, 1, 0}
};

/*
  ------------------------------------------------------------------------------
  handler
*/

void
handler(int signal)
{
	/* Try to shut everything down. */
	bb_i2c_close(pi, sda);
	pigpio_stop(pi);

	exit(EXIT_FAILURE);
}

/*
  ------------------------------------------------------------------------------
  traccess
*/

static int
traccess(int pi, enum trname trn, int read, void *xfer)
{
	int rc;
	struct tr *reg = &trs[trn];
	char *zip;
	int zi = 0;
	char *buf;
	int i;

	if (0 != read) {
		/* this is a read */
		zip = malloc(12);
		buf = malloc(reg->width);
	} else {
		/* this is a write */
		zip = malloc(12 + reg->width);
	}

	/* Write the Device Address */
	zip[zi++] = 4;
	zip[zi++] = i2c_address;

	if (0 != read) {
		/* this is a read */

		/* Write the Register Offset */
		zip[zi++] = 2;
		zip[zi++] = 7;
		zip[zi++] = 1;
		zip[zi++] = reg->offset;
		zip[zi++] = 3;
		zip[zi++] = 2;
		zip[zi++] = 6;
		zip[zi++] = reg->width;
		zip[zi++] = 3;
	} else {
		/* this is a write */

		/* Write the Register Offset */
		zip[zi++] = 2;
		zip[zi++] = 7;
		zip[zi++] = 1 + reg->width;
		zip[zi++] = (0x80 | reg->offset);

		switch (reg->width) {
		case 1:
			zip[zi++] = *((unsigned char *)xfer);
			break;
		case 2:
		{
			unsigned short p = *((unsigned short *)xfer);
			zip[zi++] = (p & 0xff);
			zip[zi++] = (p & 0xff00) >> 8;
		}
		break;
		case 4:
		{
			unsigned long p = *((unsigned long *)xfer);
			zip[zi++] = (p & 0xff);
			zip[zi++] = (p & 0xff00) >> 8;
			zip[zi++] = (p & 0xff0000) >> 16;
			zip[zi++] = (p & 0xff000000) >> 24;
		}
		break;
		default:
			fprintf(stderr, "%d - Internal Error!\n", __LINE__);
			break;
		}

		zip[zi++] = 3;
	}

	/* End the Sequence */
	zip[zi++] = 0;

	if (0 != verbose) {
		printf("zip: ");

		for (i = 0; i < zi; ++i)
			printf("%02x ", zip[i]);

		puts("");
	}

	if (0 != read)
		rc = bb_i2c_zip(pi, sda, zip, zi, buf, reg->width);
	else
		rc = bb_i2c_zip(pi, sda, zip, zi, NULL, 0);

	free(zip);

	if ((0 != verbose) && (0 != read)) {
		printf("buf: "); 

		for (i = 0; i < reg->width; ++i)
			printf("%02x ", buf[i]);

		puts("");
	}

	if (0 != read) {
		/* this is a read */
		if (reg->width != rc) {
			fprintf(stderr,
				"%d: bb_i2c_zip() failed: %d\n", __LINE__, rc);

			if (0 != read)
				free(buf);

			return -1;
		}

		switch (reg->width) {
		case 1:
			*((unsigned char *)xfer) = buf[0];
			break;
		case 2:
			*((unsigned short *)xfer) = (buf[1] << 8) | buf[0];
			break;
		case 4:
			*((unsigned int *)xfer) =
				(buf[3] << 24) | (buf[2] << 16) |
				(buf[1] << 8) | buf[0];
			break;
		default:
			fprintf(stderr, "Invalid Width: %d\n", reg->width);
			break;
		}

		free(buf);
	} else {
		/* this is a write */
		if (0 != rc) {
			fprintf(stderr,
				"%d: bb_i2c_zip() failed: %d\n", __LINE__, rc);

			if (0 != read)
				free(buf);

			return -1;
		}
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  usage
*/

static void
usage(const char *prog, int exit_code)
{
	printf("Usage: %s [-abcdt]\n", prog);
	printf("  -a --ipaddress  Hostname or IP Address (default localhost)\n"
	       "  -A --ocr1a      Set the OCR1A register to the given value\n"
	       "  -c --clockpin   Pin (BCM) to use as I2C scl (default %d)\n"
	       "  -d --datapin    Pin (BCM) to use as I2C sda (default %d)\n"
	       "  -h --help       Help\n"
	       "  -i --i2caddress I2C address (default %d)\n"
	       "  -p --port       Port number\n"
	       "  -P --pllcsr     Set the PLLCSR register to the given value\n"
	       "  -s --speed      I2C clock rate (Hz, default %d)\n"
	       "  -t --test       Run a test loop for given number of times\n"	
	       "  -T --tccr1      Set the TCCR1 register to the given value\n"
	       "  -v --verbose    Spew extra info...\n",
	       i2c_address, speed, scl, sda);

	exit(1);
}

/*
  ------------------------------------------------------------------------------
  main
*/

int
main(int argc, char *argv[])
{
	int rc;
	unsigned short magic;
	unsigned short project;
	unsigned short version;
	int test = 1;
	char ip_address[NAME_MAX];
	char ip_port[NAME_MAX];
	unsigned char pllcsr;
	int write_pllcsr = 0;
	unsigned char tccr1;
	int write_tccr1 = 0;
	unsigned char ocr1a;
	int write_ocr1a = 0;

	strcpy(ip_address, "localhost");
	strcpy(ip_port, "8888");

	/*
	  Get the Options
	*/

	while (1) {
		static const struct option lopts[] = {
			{ "ipaddress",  1, 0, 'a' },
			{ "ocr1a",      1, 0, 'A' },
			{ "clockpin",   1, 0, 'c' },
			{ "datapin",    1, 0, 'd' },
			{ "help",       1, 0, 'h' },
			{ "i2caddress", 1, 0, 'p' },
			{ "port",       1, 0, 'p' },
			{ "pllcsr",     1, 0, 'P' },
			{ "speed",      1, 0, 's' },
			{ "test",       1, 0, 't' },
			{ "tccr1",      1, 0, 'T' },
			{ "verbose",    1, 0, 'v' },
			{ NULL, 0, 0, 0 },
		};

		int c;

		c = getopt_long(argc, argv, "a:A:c:d:hi:p:P:s:t:T:v",
				lopts, NULL);

		if (c == -1)
			break;

		switch (c) {
		case 'a':
			strcpy(ip_address, optarg);
			break;
		case 'A':
			ocr1a = (unsigned char)strtoul(optarg, NULL, 0);
			write_ocr1a = 1;
			break;
		case 'c':
			scl = strtol(optarg, NULL, 0);
			break;
		case 'd':
			sda = strtol(optarg, NULL, 0);
			break;
		case 'h':
			usage(argv[0], EXIT_SUCCESS);
			break;
		case 'i':
			i2c_address = strtol(optarg, NULL, 0);
			break;
		case 'p':
			strcpy(ip_port, optarg);
			break;
		case 'P':
			pllcsr = (unsigned char)strtoul(optarg, NULL, 0);
			write_pllcsr = 1;
			break;
		case 's':
			speed = strtol(optarg, NULL, 0);
			break;
		case 't':
			test = strtol(optarg, NULL, 0);
			break;
		case 'T':
			tccr1 = (unsigned char)strtoul(optarg, NULL, 0);
			write_tccr1 = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			usage(argv[0], EXIT_FAILURE);
			break;
		}
	}

	/*
	  Set up the Socket Connection
	*/

	if (0 != verbose)
		printf("--> Starting pigpio with (%s, %s)\n",
		       ip_address, ip_port);

	pi = pigpio_start(ip_address, ip_port);

	if (0 > pi) {
		fprintf(stderr, "pigpio_start() failed: %d\n", pi);

		return EXIT_FAILURE;
	}

	/*
	  Open Bit Banged I2C
	*/

	if (0 != verbose)
		printf("--> Opening pigpio I2C with (, %d, %d, %d)\n",
		       sda, scl, speed);

	rc = bb_i2c_open(pi, sda, scl, speed);

	if (0 != rc) {
		fprintf(stderr, "bb_i2c_open() failed: 0x%x\n", rc);
		pigpio_stop(pi);

		return EXIT_FAILURE;
	}

	/*
	  Catch Signals
	*/

	signal(SIGHUP, handler);
	signal(SIGINT, handler);
	signal(SIGCONT, handler);
	signal(SIGTERM, handler);

	while (0 < test--) {
		/*
		  Verify the Magic Number, and get the Project and Version
		*/

		if (EXIT_SUCCESS != traccess(pi, trmagic, 1, &magic) ||
		    EXIT_SUCCESS != traccess(pi, trproject, 1, &project) ||
		    EXIT_SUCCESS != traccess(pi, trversion, 1, &version)) {
			fprintf(stderr, "Read Failed\n");
			rc = EXIT_FAILURE;
			goto exit;
		}

		if (0xbacd != magic) {
			fprintf(stderr, "Bad Magic Number: 0x%x\n", magic);
			rc = EXIT_FAILURE;
			goto exit;
		}

		printf("Project: 0x%04x Version: 0x%04x\n", project, version);

		/*
		  Write as Directed
		*/

		if (0 != write_pllcsr) {
			if (EXIT_SUCCESS !=
			    traccess(pi, trpllcsr, 0, &pllcsr)) {
				fprintf(stderr, "Read Failed\n");
				rc = EXIT_FAILURE;
				goto exit;
			}
		}

		if (0 != write_tccr1) {
			if (EXIT_SUCCESS !=
			    traccess(pi, trtccr1, 0, &tccr1)) {
				fprintf(stderr, "Read Failed\n");
				rc = EXIT_FAILURE;
				goto exit;
			}
		}

		if (0 != write_ocr1a) {
			if (EXIT_SUCCESS !=
			    traccess(pi, trocr1a, 0, &ocr1a)) {
				fprintf(stderr, "Read Failed\n");
				rc = EXIT_FAILURE;
				goto exit;
			}
		}

		/*
		  Read Everything
		*/

		if (EXIT_SUCCESS != traccess(pi, trpllcsr, 1, &pllcsr) ||
		    EXIT_SUCCESS != traccess(pi, trtccr1, 1, &tccr1) ||
		    EXIT_SUCCESS != traccess(pi, trocr1a, 1, &ocr1a)) {
			fprintf(stderr, "Read Failed\n");
			rc = EXIT_FAILURE;
			goto exit;
		}

		printf("PLLCSR=0x%x TCCR1=0x%x OCR1A=0x%x\n",
		       pllcsr, tccr1, ocr1a);
	}

	rc = EXIT_SUCCESS;

 exit:

	/*
	  Close the Bit Banged I2C Interface
	*/

	bb_i2c_close(pi, sda);

	/*
	  Shut Down "pigpiod"
	*/

	pigpio_stop(pi);

	return rc;
}

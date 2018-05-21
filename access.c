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

static int sda = 2;
static int scl = 3;
static int speed = 100000;
static int i2c_address = -1;
static int pi = -1;

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
	trdummy1 = 3,
	trdummy2 = 4,
	trdummy4 = 5
};

struct tr trs[] = {
	{"magic", trmagic, 2, 1},
	{"project", trproject, 2, 1},
	{"version", trversion, 2, 1},
	{"dummy1", trdummy1, 1, 0},
	{"dummy2", trdummy2, 2, 0},
	{"dummy4", trdummy4, 4, 0}
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

/*#define DEBUG*/

static int
traccess(int pi, enum trname trn, int read, void *xfer)
{
	int rc;
	struct tr *reg = &trs[trn];
	char *zip;
	int zi = 0;
	char *buf;
#ifdef DEBUG
	int i;
#endif

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

#ifdef DEBUG
	printf("zip: ");

	for (i = 0; i < zi; ++i)
		printf("%02x ", zip[i]);

	puts("");
#endif

	if (0 != read)
		rc = bb_i2c_zip(pi, sda, zip, zi, buf, reg->width);
	else
		rc = bb_i2c_zip(pi, sda, zip, zi, NULL, 0);

	free(zip);

#ifdef DEBUG
	if (0 != read) {
		printf("buf: "); 

		for (i = 0; i < reg->width; ++i)
			printf("%02x ", buf[i]);

		puts("");
	}
#endif

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

/*
  ------------------------------------------------------------------------------
  usage
*/

static void
usage(const char *prog, int exit_code)
{
	printf("Usage: %s [-abcdt]\n", prog);
	printf("  -a --ipaddress  Hostname or IP Address (default localhost)\n"
	       "  -c --clockpin   Pin (BCM) to use as I2C scl (default %d)\n"
	       "  -d --datapin    Pin (BCM) to use as I2C sda (default %d)\n"
	       "  -h --help       Help\n"
	       "  -i --i2caddress I2C address (default %d)\n"
	       "  -p --port       Port number\n"
	       "  -s --speed      I2C clock rate (Hz, default %d)\n"
	       "  -t --test       Run a test loop for given number of times\n",
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
	unsigned char dummy1;
	unsigned short dummy2;
	unsigned long dummy4;
	int test = 1;
	char ip_address[NAME_MAX];
	char ip_port[NAME_MAX];

	strcpy(ip_address, "localhost");
	strcpy(ip_port, "8888");

	/*
	  Get the Options
	*/

	while (1) {
		static const struct option lopts[] = {
			{ "ipaddress",  1, 0, 'a' },
			{ "clockpin",   1, 0, 'c' },
			{ "datapin",    1, 0, 'd' },
			{ "help",       1, 0, 'h' },
			{ "i2caddress", 1, 0, 'p' },
			{ "port",       1, 0, 'p' },
			{ "speed",      1, 0, 's' },
			{ "test",       1, 0, 't' },
			{ NULL, 0, 0, 0 },
		};

		int c;

		c = getopt_long(argc, argv, "a:c:d:hi:p:s:t:", lopts, NULL);

		if (c == -1)
			break;

		switch (c) {
		case 'a':
			strcpy(ip_address, optarg);
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
		case 's':
			speed = strtol(optarg, NULL, 0);
			break;
		case 't':
			test = strtol(optarg, NULL, 0);
			break;
		default:
			usage(argv[0], EXIT_FAILURE);
			break;
		}
	}

	/*
	  Set up the Socket Connection
	*/

	pi = pigpio_start(ip_address, ip_port);

	if (0 > pi) {
		fprintf(stderr, "pigpio_start() failed: %d\n", pi);

		return EXIT_FAILURE;
	}

	/*
	  Open Bit Banged I2C
	*/

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
		  Read Dummys
		*/

		if (EXIT_SUCCESS != traccess(pi, trdummy1, 1, &dummy1) ||
		    EXIT_SUCCESS != traccess(pi, trdummy2, 1, &dummy2) ||
		    EXIT_SUCCESS != traccess(pi, trdummy4, 1, &dummy4)) {
			fprintf(stderr, "Read Failed\n");
			rc = EXIT_FAILURE;
			goto exit;
		}

		printf("dummys are 0x%02x 0x%04x 0x%08lx\n",
		       dummy1, dummy2, dummy4);

		/*
		  Write Dummys
		*/

		dummy1 = ~dummy1;
		dummy2 = ~dummy2;
		dummy4 = ~dummy4;

		if ((EXIT_SUCCESS != traccess(pi, trdummy1, 0, &dummy1)) ||
		    (EXIT_SUCCESS != traccess(pi, trdummy2, 0, &dummy2)) ||
		    (EXIT_SUCCESS != traccess(pi, trdummy4, 0, &dummy4))) {
			fprintf(stderr, "Write Failed\n");
			rc = EXIT_FAILURE;
			goto exit;
		}

		/*
		  Read Dummys Again
		*/

		if (EXIT_SUCCESS != traccess(pi, trdummy1, 1, &dummy1) ||
		    EXIT_SUCCESS != traccess(pi, trdummy2, 1, &dummy2) ||
		    EXIT_SUCCESS != traccess(pi, trdummy4, 1, &dummy4)) {
			fprintf(stderr, "Read Failed\n");
			rc = EXIT_FAILURE;
			goto exit;
		}

		printf("dummys are 0x%02x 0x%04x 0x%08lx\n",
		       dummy1, dummy2, dummy4);
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

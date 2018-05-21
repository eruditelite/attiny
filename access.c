/*
  bbdaccess.c

  Access to target registers using pigpio via socket interface.

  Each project can define "registers" that can be accessed via i2c.
  Each register will have the following:

  1) A name.
  2) An offset from 0...255.
  3) A width.
  4) An access property, read only or read write.

  Bit 8 is the read/write bit in the command, bits 6:0 are the offset.

  All projects should have the following.

  magic, 0x00, 2, ro
  project, 0x01, 2, ro
  version, 0x02, 2, ro
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <pigpiod_if2.h>

#define SDA 2
#define SCL 3
#define BAUD 100000
static int i2c_address;
static int pi;

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
	bb_i2c_close(pi, SDA);
	pigpio_stop(pi);

	exit(EXIT_SUCCESS);
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
		rc = bb_i2c_zip(pi, SDA, zip, zi, buf, reg->width);
	else
		rc = bb_i2c_zip(pi, SDA, zip, zi, NULL, 0);

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

	if (4 > argc) {
		fprintf(stderr,
			"I2C address, IP address, and IP port are required!\n");

		return EXIT_FAILURE;
	}

	i2c_address = (int)strtoul(argv[1], NULL, 0);

	/*
	  Set up the Socket Connection
	*/

	pi = pigpio_start(argv[2], argv[3]);

	if (0 > pi) {
		fprintf(stderr, "pigpio_start() failed: %d\n", pi);

		return EXIT_FAILURE;
	}

	/*
	  Open Bit Banged I2C
	*/

	rc = bb_i2c_open(pi, SDA, SCL, BAUD);

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

	printf("dummys are 0x%02x 0x%04x 0x%08lx\n", dummy1, dummy2, dummy4);

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

	printf("dummys are 0x%02x 0x%04x 0x%08lx\n", dummy1, dummy2, dummy4);

	rc = EXIT_SUCCESS;

 exit:

	/*
	  Close the Bit Banged I2C Interface
	*/

	bb_i2c_close(pi, SDA);

	/*
	  Shut Down "pigpiod"
	*/

	pigpio_stop(pi);

	return rc;
}

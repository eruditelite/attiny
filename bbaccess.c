/*
  access.c

  Access to target registers.

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
#include <string.h>
#include <pigpio.h>

#define SDA 2
#define SCL 3

static int address;

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
	trdelay = 3
};

struct tr trs[] = {
	{"magic", 0, 2, 1},
	{"project", 1, 2, 1},
	{"version", 2, 2, 1},
	{"delay", 3, 4, 0}
};

/*
  ------------------------------------------------------------------------------
  rread
*/

int
rread(enum trname trn, void *buffer)
{
	int rc;
	char *buf;
	struct tr *reg = &trs[trn];

	buf = malloc(reg->width);

	char zip[] = {
		4, address,	/* Write the Address */
		2, 7, 1, reg->offset, 2, 6, reg->width, 3, /* The Read */
		0
	};

	rc = bbI2CZip(SDA, zip, sizeof(zip), buf, sizeof(buf));

	if (reg->width != rc) {
		fprintf(stderr, "%d: bbI2CZip() failed: 0x%x\n",
			__LINE__, rc);
		free(buf);
		return -1;
	}

	switch (reg->width) {
	case 1:
		*((unsigned char *)buffer) =
			buf[0];
		break;
	case 2:
		*((unsigned short *)buffer) =
			(buf[1] << 8) | buf[0];
		break;
	case 4:
		*((unsigned int *)buffer) =
			(buf[3] << 24) | (buf[2] << 16) |
			(buf[1] << 8) | buf[0];
		break;
	default:
		fprintf(stderr, "Invalid Width: %d\n", reg->width);
		break;
	}

	free(buf);

	return EXIT_SUCCESS;
}

/*
  ------------------------------------------------------------------------------
  rwrite
*/

int
rwrite(enum trname trn, unsigned char *buffer)
{
	int rc;
	int i = 0;
	int j;
	struct tr *reg = &trs[trn];
	char *zip;

	zip = malloc(7 + reg->width);

	zip[i++] = 4;
	zip[i++] = address;
	zip[i++] = 2;
	zip[i++] = 7;
	zip[i++] = reg->width + 1;

	for (j = 0; j < reg->width; ++j)
		zip[i++] = buffer[j];

	zip[i++] = 3;
	zip[i++] = 0;

	rc = bbI2CZip(SDA, zip, sizeof(zip), NULL, 0);

	if (0 < rc) {
		fprintf(stderr, "%d: bbI2CZip() failed: 0x%x\n",
			__LINE__, rc);
		return -1;
	}

	return EXIT_SUCCESS;
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
	unsigned int delay;
	int write = 0;

	if (2 > argc) {
		fprintf(stderr, "I2C address is required!\n");

		return EXIT_FAILURE;
	}

	address = (int)strtoul(argv[1], NULL, 0);

	/*
	  Set up pigpio for Bit Banged I2C
	*/

	rc = gpioInitialise();

	if (0 > rc) {
		fprintf(stderr, "gpioInitialise() Failed\n");
		return EXIT_FAILURE;
	}

	rc = bbI2COpen(SDA, SCL, 100000);

	if (0 != rc) {
		fprintf(stderr, "bbI2COpen() Failed: 0x%x\n", rc);
		gpioTerminate();
		return EXIT_FAILURE;
	}

	/* Verify the Magic Number, and get the Project and Version */

	if (EXIT_SUCCESS != rread(trmagic, &magic) ||
	    EXIT_SUCCESS != rread(trproject, &project) ||
	    EXIT_SUCCESS != rread(trversion, &version)) {
		fprintf(stderr, "Read Failed\n");

		return EXIT_FAILURE;
	}

	if (0xbacd != magic) {
		fprintf(stderr, "Bad Magic Number: 0x%x\n", magic);

		return EXIT_FAILURE;
	}

	printf("Project: 0x%04x Version: 0x%04x\n", project, version);

	/* Write a new delay value if indicated... */

	if (0 != write) {
		if (EXIT_SUCCESS != rwrite(trdelay,
					   (unsigned char *)&delay)) {
			fprintf(stderr, "Write Failed\n");

			return EXIT_FAILURE;
		}
	}

	/* Display the current delay value. */

	if (EXIT_SUCCESS != rread(trdelay, &delay)) {
		fprintf(stderr, "Read Failed\n");

		return EXIT_FAILURE;
	}

	printf("Delay: %u\n", delay);

	/*
	  Shut Down "pigpio"
	*/

	rc = bbI2CClose(SDA);

	if (0 != rc) {
		fprintf(stderr, "bbI2CClose() Failed: 0x%x\n", rc);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

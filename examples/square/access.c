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
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

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
	trocr1a = 5,
	trocr1c = 6
};

struct tr trs[] = {
	{"magic", 0, 2, 1},
	{"project", 1, 2, 1},
	{"version", 2, 2, 1},
	{"pllcsr", 3, 1, 0},
	{"tccr1", 4, 1, 0},
	{"ocr1a", 5, 1, 0},
	{"ocr1c", 6, 1, 0}
};

/*
  ------------------------------------------------------------------------------
  rread
*/

int
rread(int fd, enum trname trn, void *buffer)
{
	unsigned char *buf;
	struct tr *reg = &trs[trn];

	buf = malloc(reg->width);

	/* Write the Offset */

	buf[0] = reg->offset;

	if (1 != write(fd, buf, 1)) {
		fprintf(stderr, "write() failed: %s\n", strerror(errno));
		free(buf);

		return -1;
	}

	if (reg->width != read(fd, buf, reg->width)) {
		fprintf(stderr,	"read() failed: %s\n", strerror(errno));
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
rwrite(int fd, enum trname trn, unsigned char *buffer)
{
	int i;
	unsigned char *buf;
	struct tr *reg = &trs[trn];

	buf = malloc(reg->width + 1);

	/* Write the Offset and Data */

	buf[0] = (0x80 | reg->offset);

	for (i = 0; i < reg->width; ++i)
		buf[(i + 1)] = buffer[i];

	if ((1 + reg->width) != write(fd, buf, (1 + reg->width))) {
		fprintf(stderr, "write() failed: %s\n", strerror(errno));
		free(buf);

		return -1;
	}

	free(buf);

	return EXIT_SUCCESS;
}

/*
  ------------------------------------------------------------------------------
  main
*/

int
main(int argc, char *argv[])
{
	int fd;
	unsigned short magic;
	unsigned short project;
	unsigned short version;
	unsigned char value;
	unsigned char pllcsr;
	unsigned char tccr1;
	unsigned char ocr1a;
	unsigned char ocr1c;
	int write = 0;

	if (5 == argc) {
		write = 1;

		pllcsr = (unsigned char)strtoul(argv[1], NULL, 0);
		tccr1 = (unsigned char)strtoul(argv[2], NULL, 0);
		ocr1a = (unsigned char)strtoul(argv[3], NULL, 0);
		ocr1c = (unsigned char)strtoul(argv[4], NULL, 0);

		printf("\n-- Writing --\n"
		       "PLLCSR:0x%02x TCCR1:0x%02x "
		       "OCR1A:0x%02x/%u OCR1C:0x%02x/%u\n\n",
		       pllcsr, tccr1, ocr1a, ocr1a, ocr1c, ocr1c);
	}

	/* Open the I2C Bus */
	if (0 > (fd = open("/dev/i2c-1", O_RDWR))) {
		printf("Open Failed: %s\n", strerror(errno));

		return EXIT_FAILURE;
	}
	
	if (0 > ioctl(fd, I2C_SLAVE, 8)) {
		printf("IOCTL Failed: %s\n", strerror(errno));

		return EXIT_FAILURE;
	}

	/* Verify the Magic Number, and get the Project and Version */

	if (EXIT_SUCCESS != rread(fd, trmagic, &magic) ||
	    EXIT_SUCCESS != rread(fd, trproject, &project) ||
	    EXIT_SUCCESS != rread(fd, trversion, &version)) {
		fprintf(stderr, "Read Failed\n");

		return EXIT_FAILURE;
	}

	if (0xbacd != magic) {
		fprintf(stderr, "Bad Magic Number!\n");

		return EXIT_FAILURE;
	}

	printf("Project: 0x%04x Version: 0x%04x\n", project, version);

	/* Change Things... */

	if (0 != write) {
		if (EXIT_SUCCESS !=
		    rwrite(fd, trpllcsr, (unsigned char *)&pllcsr)) {
			fprintf(stderr, "Write Failed\n");
			return EXIT_FAILURE;
		}

		if (EXIT_SUCCESS !=
		    rwrite(fd, trtccr1, (unsigned char *)&tccr1)) {
			fprintf(stderr, "Write Failed\n");

			return EXIT_FAILURE;
		}

		if (EXIT_SUCCESS !=
		    rwrite(fd, trocr1a, (unsigned char *)&ocr1a)) {
			fprintf(stderr, "Write Failed\n");

			return EXIT_FAILURE;
		}

		if (EXIT_SUCCESS !=
		    rwrite(fd, trocr1c, (unsigned char *)&ocr1c)) {
			fprintf(stderr, "Write Failed\n");

			return EXIT_FAILURE;
		}
	}

	/* Read PLLCSR */

	if (EXIT_SUCCESS != rread(fd, trpllcsr, &pllcsr)) {
		fprintf(stderr, "Read Failed\n");

		return EXIT_FAILURE;
	}

	printf("PLLCSR: 0x%02x\n", pllcsr);

	/* Read TCCR1 */

	if (EXIT_SUCCESS != rread(fd, trtccr1, &value)) {
		fprintf(stderr, "Read Failed\n");

		return EXIT_FAILURE;
	}

	printf(" TCCR1: 0x%02x\n", value);

	/* Read OCR1* */

	if (EXIT_SUCCESS != rread(fd, trocr1a, &value)) {
		fprintf(stderr, "Read Failed\n");

		return EXIT_FAILURE;
	}

	printf(" OCR1A: %d\n", value);

	if (EXIT_SUCCESS != rread(fd, trocr1c, &value)) {
		fprintf(stderr, "Read Failed\n");

		return EXIT_FAILURE;
	}

	printf(" OCR1C: %d\n", value);

	close(fd);

	return EXIT_SUCCESS;
}

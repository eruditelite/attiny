/*
  access.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

/*
  ------------------------------------------------------------------------------
  access_read
*/

int
access_read(int fd, void *buffer, int length)
{
	if (length != read(fd, buffer, length)) {
		fprintf(stderr,	"access_read() failed: %s\n", strerror(errno));
			
		return -1;
	}

	return length;
}

/*
  ------------------------------------------------------------------------------
  access_write
*/

int
access_write(int fd, const void *buffer, int length)
{
	if (length != write(fd, buffer, length)) {
		fprintf(stderr, "access_write() failed: %s\n", strerror(errno));

		return -1;
	}

	return length;
}

/*
  ------------------------------------------------------------------------------
  main
*/

int
main(int argc, char *argv[])
{
	int fd;
	unsigned char buffer[2];

	/* Open the I2C Bus */
	if (0 > (fd = open("/dev/i2c-1", O_RDWR))) {
		printf("Open Failed: %s\n", strerror(errno));

		return EXIT_FAILURE;
	}
	
	if (0 > ioctl(fd, I2C_SLAVE, 8)) {
		printf("IOCTL Failed: %s\n", strerror(errno));

		return EXIT_FAILURE;
	}

	/* Verify the Magic Number */

	buffer[0] = 0xff;

	if (1 != access_write(fd, buffer, 1)) {
		fprintf(stderr, "Write Failed\n");

		return EXIT_FAILURE;
	}

	if (2 != access_read(fd, buffer, 2)) {
		fprintf(stderr, "Read Failed\n");

		return EXIT_FAILURE;
	}

	if ((0xba != buffer[0]) || (0xcd != buffer[1])) {
		printf("Bad Magic Number!\n");

		return EXIT_FAILURE;
	}

	/* Get the Program and Version */

	buffer[0] = 0xfe;

	if (1 != access_write(fd, buffer, 1)) {
		fprintf(stderr, "Write Failed\n");

		return EXIT_FAILURE;
	}

	if(2 != access_read(fd, buffer, 2)) {
		fprintf(stderr, "Write Failed\n");

		return EXIT_FAILURE;
	}

	printf("Project: 0x%02x Version: 0x%02x\n", buffer[0], buffer[1]);

	close(fd);

	return EXIT_SUCCESS;
}

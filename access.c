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

#if 0
//----- READ BYTES -----
length = 4;			//<<< Number of bytes to read
if (read(file_i2c, buffer, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
{
	//ERROR HANDLING: i2c transaction failed
	printf("Failed to read from the i2c bus.\n");
}
else
{
	printf("Data read: %s\n", buffer);
}

	
//----- WRITE BYTES -----
buffer[0] = 0x01;
buffer[1] = 0x02;
length = 2;			//<<< Number of bytes to write
if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
{
	/* ERROR HANDLING: i2c transaction failed */
	printf("Failed to write to the i2c bus.\n");
}
#endif

/*
  ------------------------------------------------------------------------------
  main
*/

int
main(int argc, char *argv[])
{
	int fd;

	/* Open the I2C Bus */
	if (0 > (fd = open("/dev/i2c-1", O_RDWR))) {
		printf("Open Failed: %s\n", strerror(errno));

		return EXIT_FAILURE;
	}
	
	if (0 > ioctl(fd, I2C_SLAVE, 8)) {
		printf("IOCTL Failed: %s\n", strerror(errno));

		return EXIT_FAILURE;
	}

	{
		unsigned char buffer[60];

		/* A Write */

		memset(buffer, 0, sizeof(buffer));
		buffer[0] = 0x20;

		if (1 != write(fd, buffer, 1)) {
			printf("Write Failed: %s\n", strerror(errno));
			close(fd);

			return EXIT_FAILURE;
		} else {
			printf("Wrote 0x%02x to 8\n", buffer[0]);
		}
	}

	{
		unsigned char buffer[60];

		/* A Read */

		memset(buffer, 0, sizeof(buffer));

		if (1 != read(fd, buffer, 1)) {
			printf("Read Failed: %s\n", strerror(errno));
			close(fd);

			return EXIT_FAILURE;
		} else {
			printf("Read 0x%02x from 8\n", buffer[0]);
		}
	}

	close(fd);

	return EXIT_SUCCESS;
}

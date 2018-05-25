/*
  main.c
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>

#include "tick.h"
#include "i2c.h"

/*
  ------------------------------------------------------------------------------
  i2c_callback
*/

void
i2c_callback(uint8_t input_buffer_length,
	     const uint8_t *input_buffer,
	     uint8_t *output_buffer_length,
	     uint8_t *output_buffer)
{
	int i;
	static uint8_t dummy1 = 0x11;
	static uint16_t dummy2 = 0x2222;
	static uint32_t dummy4 = 0x44444444;

	cli();

	for (i = 0; i < input_buffer_length; ++i) {
		switch (input_buffer[i]) {
		case 0x00:
			/* Return the magic number, 0xbacd. */
			output_buffer[0] = MAGIC & 0xff;
			output_buffer[1] = (MAGIC & 0xff00) >> 8;
			*output_buffer_length = 2;
			break;
		case 0x01:
			/* Return the project. */
			output_buffer[0] = PROJECT & 0xff;
			output_buffer[1] = (PROJECT & 0xff00) >> 8;
			*output_buffer_length = 2;
			break;
		case 0x02:
			/* Return the version. */
			output_buffer[0] = VERSION & 0xff;
			output_buffer[1] = (VERSION & 0xff00) >> 8;
			*output_buffer_length = 2;
			break;
		case 0x03:
			/* Return dummy1. */
			output_buffer[0] = dummy1;
			*output_buffer_length = 1;
			break;
		case 0x83:
			/* Set dummy1. */
			dummy1 = input_buffer[1];
			break;
		case 0x04:
			/* Return dummy2. */
			output_buffer[0] = dummy2 & 0xff;
			output_buffer[1] = (dummy2 & 0xff00) >> 8;
			*output_buffer_length = 2;
			break;
		case 0x84:
			/* Set dummy2. */
			dummy2 = ((unsigned short)(input_buffer[2]) << 8) |
				((unsigned short)(input_buffer[1]));
			break;
		case 0x05:
			/* Return dummy4. */
			output_buffer[0] = dummy4 & 0xff;
			output_buffer[1] = (dummy4 & 0xff00) >> 8;
			output_buffer[2] = (dummy4 & 0xff0000) >> 16;
			output_buffer[3] = (dummy4 & 0xff000000) >> 24;
			*output_buffer_length = 4;
			break;
		case 0x85:
			/* Set dummy4. */
			dummy4 = ((unsigned long)(input_buffer[4]) << 24) |
				((unsigned long)(input_buffer[3]) << 16) |
				((unsigned long)(input_buffer[2]) << 8) |
				((unsigned long)(input_buffer[1]));
			break;
		default:
			break;
		}
	}

	sei();

	return;
}

/*
  ------------------------------------------------------------------------------
  main
*/

int
main(void)
{
	/* Initialize the System */

	/* Start the Tick */
	start_tick(0);

	/* Start I2C */
	start_i2c(I2C_ADDRESS, 20);

	/* Then... */
	for (;;)
		;

	return 0;
}

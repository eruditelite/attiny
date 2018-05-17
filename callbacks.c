/*
  callbacks.c
*/

#include "attiny85_wr.h"

#include <util/delay.h>
#include <avr/io.h>
#include <usitwislave.h>

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

	for (i = 0; i < input_buffer_length; ++i) {
		switch (input_buffer[i]) {
		case 0xff:
			/* Return the magic number, 0xbacd. */
			output_buffer[0] = (MAGIC & 0xff00) >> 8;
			output_buffer[1] = MAGIC & 0xff;
			*output_buffer_length = 2;
			break;
		case 0xfe:
			/* Return the project and version */
			output_buffer[0] = PROJECT;
			output_buffer[1] = VERSION;
			*output_buffer_length = 2;
			break;
		default:
			break;
		}
	}

	return;
}

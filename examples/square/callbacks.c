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
			output_buffer[0] = PLLCSR;
			*output_buffer_length = 1;
			break;
		case 0x83:
			PLLCSR = input_buffer[1];
			break;
		case 0x04:
			output_buffer[0] = TCCR1;
			*output_buffer_length = 1;
			break;
		case 0x84:
			TCCR1 = input_buffer[1];
			break;
		case 0x05:
			output_buffer[0] = OCR1A;
			*output_buffer_length = 1;
			break;
		case 0x85:
			OCR1A = input_buffer[1];
			break;
		case 0x06:
			output_buffer[0] = OCR1C;
			*output_buffer_length = 1;
			break;
		case 0x86:
			OCR1C = input_buffer[1];
			break;
		default:
			break;
		}
	}

	return;
}

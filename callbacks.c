/*
  callbacks.c
*/

#include "attiny85_wr.h"

#include <util/delay.h>
#include <avr/io.h>
#include <usitwislave.h>

/*
  ------------------------------------------------------------------------------
  data_callback
*/

void
data_callback(uint8_t input_buffer_length,
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

/*
  ------------------------------------------------------------------------------
  idle_callback
*/

void
idle_callback(void)
{
#if 0
	int i;
	int ticks;

 	/* Set pin 2 to output. */
	DDRB |= (1 << PORTB3);

	/* Make pin low to start. */
	PORTB &= ~(1 << PORTB3);
	_delay_ms(1);

	/* Output a burst of square waves containing the number of ticks. */
	ticks = time_get_ticks();

	for (i = 0 ; i < ticks; ++i) {
		PORTB ^= (1 << PORTB3);
		_delay_us(5);
		PORTB ^= (1 << PORTB3);
		_delay_us(5);
	}

	_delay_ms(1);
#endif

	return;
}

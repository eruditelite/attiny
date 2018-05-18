/*
  attiny.c

  Handles a number of things...
*/

#include "attiny.h"		/* Must be first for F_CPU! */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <usitwislave.h>

/*
  ==============================================================================
  ==============================================================================
  Time Related Stuff
  ==============================================================================
  ==============================================================================
*/

#ifdef INCLUDE_TICKS
static unsigned long ticks;	/* rolls over every 2.4 years */
#endif  /* INCLUDE_TICKS */

/*
  ------------------------------------------------------------------------------
  time_delay_ms
*/

void
time_delay_ms(unsigned long ms)
{
	/* convert ms to us */
	ms *= 1000;

	while (0 < ms) {
		usi_twi_check();
		_delay_us(5);
		ms -= 5;
	}
}

#ifdef INCLUDE_TICKS

/*
  ------------------------------------------------------------------------------
  time_isr
*/

ISR(WDT_vect)
{
	++ticks;
}

/*
  ------------------------------------------------------------------------------
  time_get_ticks
*/

unsigned long
time_get_ticks(void)
{
	return ticks;
}

/*
  ------------------------------------------------------------------------------
  time_ms_per_tick

  At minimum divisor, and 5V, each interrupt should happen at 16 ms.
  As measured with a scope, it seems to be about 18 ms (17.60 ms to
  18.40 ms on the handful of ATTiny85s that I have).

  No idea about temperature.
*/

unsigned long
time_ms_per_tick(void)
{
	return 18;
}

/*
  ------------------------------------------------------------------------------
  time_init
*/

int
time_init(void)
{
	ticks = 3;

	/* Set up the watchdog timer. */
	WDTCR = _BV(WDIE);

	/* Enable interrupts. */
	sei();

	return 0;
}

#endif	/* INCLUDE_TICKS */

/*
  ==============================================================================
  ==============================================================================
  I2C
  ==============================================================================
  ==============================================================================
*/

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
		default:
			break;
		}
	}

	return;
}

/*
  ==============================================================================
  ==============================================================================
  The main stuff...
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  initialize
*/

void
initialize(void)
{
	return;
}

/*
  ------------------------------------------------------------------------------
  work
*/

void
work(void)
{
	for (;;)
		usi_twi_check(); /* Check for I2C Messages */

	return;
}
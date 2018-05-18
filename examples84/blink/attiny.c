/*
  attiny.c

  Handles a number of things...
*/

#include "attiny.h"		/* Must be first for F_CPU! */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <usitwislave.h>

unsigned long delay[4];

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
#if defined(__AVR_ATtiny84__)
	WDTCSR = _BV(WDIE);
#elif defined(__AVR_ATtiny85__)
	WDTCR = _BV(WDIE);
#endif

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
		case 0x3:
			/* Get delay 1. */
			output_buffer[0] = delay[0] & 0xff;
			output_buffer[1] = (delay[0] & 0xff00) >> 8;
			output_buffer[2] = (delay[0] & 0xff0000) >> 16;
			output_buffer[3] = (delay[0] & 0xff000000) >> 24;
			*output_buffer_length = 4;
			break;
		case 0x83:
			/* Set delay 1. */
			delay[0] = input_buffer[4];
			delay[0] <<= 8;
			delay[0] |= input_buffer[3];
			delay[0] <<= 8;
			delay[0] |= input_buffer[2];
			delay[0] <<= 8;
			delay[0] |= input_buffer[1];
			break;
		case 0x4:
			/* Get delay 2. */
			output_buffer[0] = delay[1] & 0xff;
			output_buffer[1] = (delay[1] & 0xff00) >> 8;
			output_buffer[2] = (delay[1] & 0xff0000) >> 16;
			output_buffer[3] = (delay[1] & 0xff000000) >> 24;
			*output_buffer_length = 4;
			break;
		case 0x84:
			/* Set delay 2. */
			delay[1] = input_buffer[4];
			delay[1] <<= 8;
			delay[1] |= input_buffer[3];
			delay[1] <<= 8;
			delay[1] |= input_buffer[2];
			delay[1] <<= 8;
			delay[1] |= input_buffer[1];
			break;
		case 0x5:
			/* Get delay 3. */
			output_buffer[0] = delay[2] & 0xff;
			output_buffer[1] = (delay[2] & 0xff00) >> 8;
			output_buffer[2] = (delay[2] & 0xff0000) >> 16;
			output_buffer[3] = (delay[2] & 0xff000000) >> 24;
			*output_buffer_length = 4;
			break;
		case 0x85:
			/* Set delay 3. */
			delay[2] = input_buffer[4];
			delay[2] <<= 8;
			delay[2] |= input_buffer[3];
			delay[2] <<= 8;
			delay[2] |= input_buffer[2];
			delay[2] <<= 8;
			delay[2] |= input_buffer[1];
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
 	/* Set pins 2, 3, and 5 to output. */
	DDRB |= (_BV(PB0) | _BV(PB1) | _BV(PB2));

	/* Make all pins low to start. */
	PORTB |= ~(_BV(PB0) | _BV(PB1) | _BV(PB2));

	return;
}

/*
  ------------------------------------------------------------------------------
  work
*/

void
work(void)
{
	unsigned long start_ticks;
	unsigned long n[3];
	int p[] = {PB0, PB1, PB2};
	int i;

	for (i = 0; i < 3; ++i) {
		delay[i] = 1000;
		n[i] = 1;
	}

	start_ticks = time_get_ticks();
	
	for (;;) {
		unsigned long ticks;

		usi_twi_check();
		ticks = time_get_ticks();
		ticks -= start_ticks;
		ticks *= time_ms_per_tick();

		for (i = 0; i < 3; ++i) {
			usi_twi_check();
			if (ticks >= (n[i] * delay[i])) {
				PORTB ^= _BV(p[i]);
				++n[i];
			}
		}

		usi_twi_check();
	}

	return;
}

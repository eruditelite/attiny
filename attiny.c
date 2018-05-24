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

#ifdef INCLUDE_TICKS

#define NUMBER_OF_INTERVALS 12

static short interval[NUMBER_OF_INTERVALS] = {-1, };
void (*interval_handler[NUMBER_OF_INTERVALS])(void) = {0, };

/*
  ------------------------------------------------------------------------------
  time_isr
*/

ISR(WDT_vect)
{
	int i;

	++ticks;

	for (i = 0; i < NUMBER_OF_INTERVALS; ++i) {
		if ((0 <= interval[i]) && (0 == (ticks % interval[i])))
			(interval_handler[i])();
	}
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
  At minimum divisor, and 5V, each interrupt should happen at 16 ms.
  As measured with a scope, it seems to be about 18 ms (17.60 ms to
  18.40 ms on the handful of ATTiny85s that I have).

  No idea about temperature.
*/

#define MS_TO_TICKS(ms) (ms / 18)
#define TICKS_TO_MS(ticks) (ticks * 18)

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

ISR(TIM0_COMPA_vect)
{
	usi_twi_check();
}

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
	unsigned long delay;

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
		case 0x04:
		case 0x05:
			/* Read Delay */
			delay =	TICKS_TO_MS(interval[(input_buffer[i] - 0x03)]);
			output_buffer[0] = delay & 0xff;
			output_buffer[1] = (delay & 0xff00) >> 8;
			output_buffer[2] = (delay & 0xff0000) >> 16;
			output_buffer[3] = (delay & 0xff000000) >> 24;
			*output_buffer_length = 4;
			break;
		case 0x83:
		case 0x84:
		case 0x85:
			/* Write Delay */
			delay =	((unsigned long)(input_buffer[4]) << 24) |
				((unsigned long)(input_buffer[3]) << 16) |
				((unsigned long)(input_buffer[2]) << 8) |
				((unsigned long)(input_buffer[1]));
			delay = MS_TO_TICKS(delay);
			interval[(input_buffer[i] - 0x83)] = delay;
			break;
		default:
			break;
		}
	}

	sei();

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
	/* Start Timer/Counter0 to Check for I2C Messages */
	TCCR0A = _BV(WGM01);
	TCCR0B = _BV(CS01);
	OCR0A = 20;
	TIMSK0 = _BV(OCIE0A);

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
		;

	return;
}

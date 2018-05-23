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
	/*
	  Output Square Wave on PortB 1 (pin 6)

	  Input is (F_CPU / divisor).  So, for 8 MHz and a divisor of
	  64, 100 means 800 us.

	  When high speed mode is enabled, multiply by 8, so 64 MHz.

	  OCR1C is the period.  OCR1A is the number of counts the
	  output will be high.
	*/

	/* Make pin 1 an output. */
	DDRB |= _BV(PB1);

	/* Enable high speed mode! */
	PLLCSR |= _BV(PLLE);
	PLLCSR |= _BV(PCKE);

	TCCR1 =
		/* Reset Timer/Counter1 after a compare match with OCR1C */
		_BV(CTC1) |
		/* Enable PWM Mode */
		_BV(PWM1A) |
		/* Timer/Counter1 is PCK/CK divided by 64 */
		_BV(CS11) |
		/* Toggle OC1A */
		_BV(COM1A0);

	/* PWM, Phase Correct */
	TCCR0A = _BV(WGM01);

	OCR1A = 127;		/* Count to toggle OC1A */
	OCR1C = 255;		/* Count to reset Timer/Counter1 */

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

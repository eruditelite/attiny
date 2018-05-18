/*
  work.c
*/

#include "attiny85_wr.h"

#include <avr/io.h>
#include <usitwislave.h>

/*
  ------------------------------------------------------------------------------
  initialize
*/

void
initialize(void)
{
	/*
	  Output Square Waves on PortB 1, 3, and 4
	*/

	/* Make pin 1 an output. */
	DDRB |= _BV(PB1);

	/* Enable high speed mode! */
	PLLCSR |= _BV(PLLE);
	PLLCSR |= _BV(PCKE);

	TCCR1 =
		/* Reset Timer/Counter1 after a compare match with OCR1C */
		_BV(CTC1) |
		/* Timer/Counter1 is PCK/CK divided by 64 */
		_BV(CS11) |
		/* Toggle OC1A */
		_BV(COM1A0);

	/*
	  Input is (F_CPU / divisor).  So, for 8 MHz and a divisor of
	  64, 100 means 800 us.

	  When high speed mode is enabled, multiply by 8, so 64 MHz.
	*/

	OCR1A = 100;		/* Count to toggle OC1A */
	OCR1C = 100;		/* Count to reset Timer/Counter1 */

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
		usi_twi_check();
}

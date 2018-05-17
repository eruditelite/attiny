/*
  time.c
*/

#include "attiny85_wr.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <usitwislave.h>

static unsigned long ticks;

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

/*
  work.c
*/

#include "attiny85_wr.h"

#include <avr/io.h>
#include <usitwislave.h>

unsigned int delay;

/*
  ------------------------------------------------------------------------------
  initialize
*/

void
initialize(void)
{
 	/* Set pins 2 and 3 to output. */
	DDRB |= ((1 << PORTB3) | (1 << PORTB4));

	/* Make both pins low to start. */
	PORTB |= ~((1 << PORTB3) | (1 << PORTB4));

	return;
}

/*
  ------------------------------------------------------------------------------
  work
*/

void
work(void)
{
	delay = 1000;
	
	for (;;) {
		PORTB ^= (1 << PORTB4);
		time_delay_ms(delay);
	}
}
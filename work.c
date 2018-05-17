/*
  work.c
*/

#include "attiny85_wr.h"

#include <avr/io.h>
#include <usitwislave.h>

/*
  ------------------------------------------------------------------------------
  work
*/

void
work(void)
{
	for (;;) {
		PORTB ^= (1 << PORTB4);
		time_delay_ms(1000);
	}
}

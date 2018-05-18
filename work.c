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

	return;
}
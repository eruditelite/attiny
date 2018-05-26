/*
  tick.c
*/

#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "tick.h"

static uint32_t tick;
static uint8_t mode;

static int16_t _callback_ticks[NUMBER_OF_CALLBACKS];
static void (*_callback[NUMBER_OF_CALLBACKS])(void);

/*
  ------------------------------------------------------------------------------
  start_tick
*/

int
start_tick(uint8_t mode_in)
{
	/* Check input. */
	if (9 < mode_in)
		return -1;

	/* Initialize internal variables. */
	tick = 0;
	mode = mode_in;

	/* Set up the watchdog timer. */
	if (0 != (mode_in & 0x8)) {
		/*
		  The top bit, WDP3, is bit 5 in the WDTCSR register.
		  So, if bit 3 is set, move it to bit 5.  The other
		  bits are in 2:0...
		*/
		mode_in &= ~0x8;
		mode_in |= (1 << 5);
	}

#if defined(__AVR_ATtiny84__)
	WDTCSR = _BV(WDIE) | mode_in;
#elif defined(__AVR_ATtiny85__)
	WDTCR = _BV(WDIE) | mode_in;
#endif

	/* Enable interrupts. */
	sei();

	return 0;
}

/*
  ------------------------------------------------------------------------------
  get_tick
*/

inline uint32_t
get_tick(void)
{
	register uint32_t return_tick;

	cli();
	return_tick = tick;
	sei();

	return return_tick;
}

/*
  ------------------------------------------------------------------------------
  ms_per_tick
*/

inline uint16_t
ms_per_tick(void)
{
	/* As the ticks are not that acurate anyway... */
	return (16 * (1 << mode));
}

/*
  ------------------------------------------------------------------------------
  set_callback
*/

int
set_callback(uint8_t slot, uint8_t periodic, uint16_t ticks,
	     void (*callback_fn)(void))
{
	cli();

	if (NUMBER_OF_CALLBACKS <= slot)
		return -1;	/* Bad Input! */

	if (0 != periodic) {
		_callback_ticks[slot] = ticks;
	} else {
		_callback_ticks[slot] = get_tick() + ticks;
		_callback_ticks[slot] |= 0x8000;
	}

	_callback[slot] = callback_fn;

	sei();

	return 0;
}

/*
  ------------------------------------------------------------------------------
  Interrupt Service Routine
*/

ISR(WDT_vect)
{
	int i;

	++tick;

	for (i = 0; i < NUMBER_OF_CALLBACKS; ++i) {
		if (0 <= _callback_ticks[i]) {
			if (0 != (0x8000 & _callback_ticks[i])) {
				/* one shot */
				if (tick >= (_callback_ticks[i] & ~0x8000)) {
					(_callback[i])();
					_callback_ticks[i] = -1;
					_callback[i] = NULL;
				}
			} else {
				/* periodic */
				if (0 == (tick % _callback_ticks[i])) {
					(_callback[i])();
				}
			}
		}
	}
}

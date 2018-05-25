/*
  tick.c
*/

#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "tick.h"

static uint32_t tick;
static uint8_t mode;

static int16_t callback[NUMBER_OF_CALLBACKS] = {-1, };
static void (*callback_handler[NUMBER_OF_CALLBACKS])(void) = {0, };

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
  add_callback
*/

int
add_callback(uint8_t periodic, uint16_t ticks, void (*callback_fn)(void))
{
	int i;

	cli();

	/* Find first unused callback entry. */
	for (i = 0; i < NUMBER_OF_CALLBACKS; ++i)
		if (-1 == callback[i])
			break;

	if (NUMBER_OF_CALLBACKS == i)
		return -1;	/* No callbacks available. */

	callback[i] = get_tick() + ticks;

	if (0 != periodic)
		callback[i] |= 0x8000;

	callback_handler[i] = callback_fn;

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

	if (UINT32_MAX == tick)
		tick = 0;
	else
		++tick;

	for (i = 0; i < NUMBER_OF_CALLBACKS; ++i) {
		if (0 <= callback[i]) {
			if (0 != (0x8000 & callback[i])) {
				/* one shot */
				if (tick >= (callback[i] & ~0x8000)) {
					(callback_handler[i])();
					callback[i] = -1;
					callback_handler[i] = NULL;
				}
			} else {
				if (0 == (tick % callback[i]))
					(callback_handler[i])();
			}
		}
	}
}

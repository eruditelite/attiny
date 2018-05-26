/*
  tick.h

  Include a system tick based on the watchdog timer.  Shortest tick is
  about 16 ms and the longest is 8 s.  Also, provide a way to set up a
  call back every so often, or once after a given number of ticks.
  Usage is fairly simple.

  -1-
  Early on, call tick_init().  The input parameter sets the number of
  WDT oscillator cycles, and thus the tick timing.  See the "Watchdog
  Timer Prescale Select" table in the datasheet for details.  Valid
  values are 0...9 which should make the tick 16 ms, 32 ms, 64 ms,
  0.125 s, 0.25 s, 0.5 s, 1 s, 2 s, 4 s, or 8 s.

  -2-
  

  NOTES

  The tick will roll over eventually.  At 16 ms, and using a 32 bit
  counter, this will take a bit over 2 years.  The scheduler handles
  roll over.

  Taking a few ATTiny85 parts from a bag, at random, and running them
  at 3.3 V and 5 V yielded the following actual tick when set to 16
  ms, 17.60 to 18.40.
*/

#ifndef TICK_H_
#define TICK_H_

#include <stddef.h>

int start_tick(uint8_t);
uint32_t get_tick(void);
uint16_t ms_per_tick();

#define MS_TO_TICKS(ms) (ms / ms_per_tick())
#define TICKS_TO_MS(ticks) (ticks * ms_per_tick())

#if defined(__AVR_ATtiny84__)
#define NUMBER_OF_CALLBACKS 8
#elif defined(__AVR_ATtiny85__)
#define NUMBER_OF_CALLBACKS 3
#endif

int set_callback(uint8_t, uint8_t, uint16_t, void (*)(void));

#endif	/* TICK_H_ */

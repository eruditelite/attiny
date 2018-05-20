/*
  attiny.h
*/

#include <usitwislave.h>

#ifndef ATTINY_H_
#define ATTINY_H_

#define F_CPU 8000000L

/*
  I2C Slave Support
*/

#if defined(__AVR_ATtiny84__)
#define I2C_ADDRESS 4
#elif defined(__AVR_ATtiny85__)
#define I2C_ADDRESS 5
#endif

#define MAGIC 0xbacd
#define PROJECT 0x0001
#define VERSION 0x0002

void i2c_callback(uint8_t, const uint8_t *, uint8_t *, uint8_t *);

/*
  Time Support

  Including ticks (at about 18 ms) is optional, and adds about 150
  bytes.  The delay function is required in all cases to allow I2C to
  work.
*/

#define INCLUDE_TICKS

#ifdef INCLUDE_TICKS
int time_init(void);
unsigned long time_get_ticks(void);
#endif

void time_delay_ms(unsigned long);

/*
  Work Support
*/

void initialize(void);
void work(void);

#endif	/* ATTINY_H_ */

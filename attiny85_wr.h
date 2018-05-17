/*
  attiny85_wr.h
*/

#include <usitwislave.h>

#ifndef ATTINY85_WR_H_
#define ATTINY85_WR_H_

#define F_CPU 1000000L

#define I2C_ADDRESS 8

#define MAGIC 0xbacd
#define PROJECT 0x01
#define VERSION 0x01

void data_callback(uint8_t, const uint8_t *, uint8_t *, uint8_t *);
void idle_callback(void);

unsigned long time_get_ticks(void);
int time_init(void);

#endif	/* ATTINY85_WR_H_ */

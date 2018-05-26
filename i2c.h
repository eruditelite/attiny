/*
  i2c.h
*/

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#if defined(__AVR_ATtiny84__)
#define DDR_USI		    DDRA
#define PORT_USI	    PORTA
#define PIN_USI		    PINA
#define PORT_USI_SDA	    PA6
#define PORT_USI_SCL	    PA4
#define PIN_USI_SDA	    PINA6
#define PIN_USI_SCL	    PINA4
#define USI_OVERFLOW_VECTOR USI_OVF_vect
#elif defined(__AVR_ATtiny85__)
#define DDR_USI		    DDRB
#define PORT_USI	    PORTB
#define PIN_USI		    PINB
#define PORT_USI_SDA	    PB0
#define PORT_USI_SCL	    PB2
#define PIN_USI_SDA	    PINB0
#define PIN_USI_SCL	    PINB2
#define USI_OVERFLOW_VECTOR USI_OVF_vect
#endif

#define USI_TWI_BUFFER_SIZE 32

int start_i2c(uint8_t, uint8_t,
	      void (*)(uint8_t, const uint8_t *, uint8_t *, uint8_t *));
void usi_twi_check(void);

#endif	/* I2C_H_ */

/*
  main.c
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "tick.h"
#include "i2c.h"

#define I2C_ADDRESS 7

#define MAGIC   0xbacd
#define PROJECT 0x0004
#define VERSION 0x0001

static uint16_t voltage;

/*
  ------------------------------------------------------------------------------
  i2c_callback
*/

void
i2c_callback(uint8_t ibl, const uint8_t *ib, uint8_t *obl, uint8_t *ob)
{
	uint8_t ibi;
	uint8_t obi = 0;

	cli();

	for (ibi = 0; ibi < ibl;) {
		switch (ib[ibi++]) {
		case 0x00:
			/* Return the magic number, 0xbacd. */
			ob[obi++] = MAGIC & 0xff;
			ob[obi++] = (MAGIC & 0xff00) >> 8;
			break;
		case 0x01:
			/* Return the project. */
			ob[obi++] = PROJECT & 0xff;
			ob[obi++] = (PROJECT & 0xff00) >> 8;
			break;
		case 0x02:
			/* Return the version. */
			ob[obi++] = VERSION & 0xff;
			ob[obi++] = (VERSION & 0xff00) >> 8;
			break;
		case 0x03:
			/* Return the voltage. */
			ob[obi++] = voltage & 0xff;
			ob[obi++] |= (voltage & 0xff00) >> 8;
		default:
			break;
		}
	}

	*obl = obi;

	sei();

	return;
}

/*
  ------------------------------------------------------------------------------
  main
*/

int
main(void)
{
	/*
	  Initialize the System
	*/

	/* Make PB1 an Output */
	DDRB |= _BV(PB1);

	/* Enable high speed mode! */
	/*PLLCSR = _BV(PCKE) | _BV(PLLE);*/

	TCCR1 =
		/* Enable PWM Mode */
		_BV(PWM1A) |
		/* Timer/Counter1 is PCK */
		_BV(CS10) |
		/* Toggle OC1A */
		_BV(COM1A0);

	OCR1A = 127;		/* Count to toggle OC1A */

	/* Use PB3 and PB4 to Measure Voltage */
	ADMUX = _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
	ADCSRA = _BV(ADEN) | _BV(ADIF) | _BV(ADIE);
	ADCSRB = 0;

	ADCSRA |= _BV(ADSC) | (_BV(ADPS1) | _BV(ADPS0));

	/*
	  Start I2C - Loop for I2C Messages
	*/

	start_i2c(I2C_ADDRESS, i2c_callback);

	/* Then... */
	for (;;)
		usi_twi_check();

	return 0;
}

/*
  ------------------------------------------------------------------------------
  Handle the "Analog Conversion Complete" Interrupt
*/

ISR(ADC_vect)
{
	/* Read the Voltage */
	voltage = ADCL;
	voltage |= (ADCH << 8);

	/* Start Another Conversion */
	ADCSRA |= _BV(ADSC);

	/* Set the PWM Output on PB1 */
	OCR1A = ((voltage & 0x3ff) >> 3) * 10;
}

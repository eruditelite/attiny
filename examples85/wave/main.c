/*
  main.c
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "tick.h"
#include "i2c.h"

#define I2C_ADDRESS 5

#define MAGIC   0xbacd
#define PROJECT 0x0004
#define VERSION 0x0001

#define WAVE_SIZE 0
#define SAMPLE_RATE 2
#define WAVE_TABLE 3

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
	uint8_t reg;

	/*
	  Initialize the System
	*/

	/* timer1... PWM output */

	DDRB |= _BV(PB4);

	PLLCSR = _BV(PCKE) | _BV(PLLE);

	TCCR1 = _BV(CS10);

	reg = GTCCR;
	reg &= ~(_BV(PWM1B) |
		 _BV(COM1B1) | _BV(COM1B0) |
		 _BV(FOC1B) | _BV(FOC1A) |
		 _BV(PSR1));
	reg |= (_BV(PWM1B) | _BV(COM1B0));
	GTCCR = reg;

	OCR1B = 0;
	OCR1C = 255;

	/* timer0... interrupt to output samples */

	TCCR0A = _BV(WGM00);
	TCCR0B = _BV(WGM02) | _BV(CS00);

	/* pin change interrupt on PB1 for I2C */

	GIMSK = _BV(PCIE);
	PCMSK = _BV(PCINT1);

	/*
	  Start the Tick
	*/

	start_tick(0);

	/*
	  Start I2C - Loop for I2C Messages
	*/

	start_i2c(I2C_ADDRESS, i2c_callback);

	/* Then... */
	for (;;)
		usi_twi_check();

	return 0;
}

ISR(TIMER0_COMPA_vect)
{
	static int index = 0;

	OCR1B = eeprom_read_byte((uint8_t *)(WAVE_TABLE + index++));

	if (index >= eeprom_read_word((uint16_t *)WAVE_SIZE))
		index = 0;
}

ISR(PCINT0_vect)
{
	if (0 == (PINB & _BV(PB1))) {
		TIMSK &= ~_BV(OCIE0A);
		OCR1B = 0;
	} else {
		OCR0A = eeprom_read_byte((uint8_t *)SAMPLE_RATE);
		TIMSK |= _BV(OCIE0A);
	}
}

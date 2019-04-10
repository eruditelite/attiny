/*
  main.c
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "i2c.h"

#define I2C_ADDRESS 4

#define MAGIC   0xbacd
#define PROJECT 0x0004
#define VERSION 0x0001

struct adc_input {
	uint16_t value;
	uint8_t admux;
};

static struct adc_input input[2];

/*
  Check for I2C Messages...
*/

ISR(TIM1_COMPA_vect)
{
	usi_twi_check();
}

/*
  ------------------------------------------------------------------------------
  i2c_callback
*/

void
i2c_callback(uint8_t ibl, const uint8_t *ib, uint8_t *obl, uint8_t *ob)
{
	uint8_t ibi;
	uint8_t obi = 0;
	int i;

	cli();

	for (ibi = 0; ibi < ibl;) {
		switch (ib[ibi]) {
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
		case 0x04:
			/* Return the voltage. */
			i = (ib[ibi] - 0x03);
			ob[obi++] = input[i].value & 0xff;
			ob[obi++] |= (input[i].value & 0xff00) >> 8;
			break;
		default:
			break;
		}

		++ibi;
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
	static int i = 0;

	/*
	  Initialize the System

	  For this example, use OC0A and OC0B to output a voltage that
	  matches the inputs.  As for the inputs, use differentials to
	  allow gain (if needed).  ADC0 (+) and ADC1 (-) for the first
	  and ADC2 (+) and ADC3 (-) as the second.
	*/

	/* Make OC0A (PB2) and OC0B (PA7) Outputs -- Start at 0% */

	DDRA = _BV(PA7);
	DDRB = _BV(PB2);

	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
	TCCR0B = _BV(CS01) | _BV(CS00);
	OCR0A = 0;
	OCR0B = 0;

	input[0].value = 0;
	input[0].admux = 0x08;

	input[1].value = 0;
	input[1].admux = 0x10;

	ADMUX = input[0].admux;
	ADCSRA = _BV(ADEN) | _BV(ADIF) | _BV(ADSC);

	/*
	  Start I2C - Use Timer1 to Check for I2C Messages
	*/

	start_i2c(I2C_ADDRESS, i2c_callback);

	TCCR1A = 0;
	TCCR1B = _BV(WGM12) | _BV(CS11);
	OCR1A = 20;
	TIMSK1 = _BV(OCIE1A);

	/* Then... */
	for (;;) {
		if (0 == (ADCSRA & _BV(ADIF)))
			continue;

		ADCSRA |= _BV(ADIF);
		input[i].value = ADCL;
		input[i].value |= (ADCH << 8);

		OCR0A = (input[0].value & 0x3ff) >> 2;
		OCR0B = (input[1].value & 0x3ff) >> 2;

		i ^= 1;
		ADMUX = input[i].admux;
		ADCSRA |= _BV(ADSC);
	}

	return 0;
}

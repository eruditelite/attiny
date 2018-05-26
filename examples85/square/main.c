/*
  main.c
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>

#include "tick.h"
#include "i2c.h"

#if defined(__AVR_ATtiny84__)
#define I2C_ADDRESS 4
#elif defined(__AVR_ATtiny85__)
#define I2C_ADDRESS 5
#endif

#define MAGIC   0xbacd
#define PROJECT 0x0002
#define VERSION 0x0001

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
			ob[obi++] = PLLCSR;
			break;
		case 0x83:
			PLLCSR = ib[ibi++];
			break;
		case 0x04:
			ob[obi++] = TCCR1;
			break;
		case 0x84:
			TCCR1 = ib[ibi++];
			break;
		case 0x05:
			ob[obi++] = OCR1A;
			break;
		case 0x85:
			OCR1A = ib[ibi++];
			break;
		case 0x06:
			ob[obi++] = OCR1C;
			break;
		case 0x86:
			OCR1C = ib[ibi++];
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
	/*
	  Initialize the System
	*/

	/* Make pin 1 an output. */
	DDRB |= _BV(PB1);

	/* Enable high speed mode! */
	PLLCSR |= _BV(PLLE);
	PLLCSR |= _BV(PCKE);

	TCCR1 =
		/* Reset Timer/Counter1 after a compare match with OCR1C */
		_BV(CTC1) |
		/* Enable PWM Mode */
		_BV(PWM1A) |
		/* Timer/Counter1 is PCK/CK divided by 64 */
		_BV(CS11) |
		/* Toggle OC1A */
		_BV(COM1A0);

	/* PWM, Phase Correct */
	TCCR0A = _BV(WGM01);

	OCR1A = 127;		/* Count to toggle OC1A */
	OCR1C = 255;		/* Count to reset Timer/Counter1 */

	/*
	  Start the Tick
	*/

	start_tick(0);

	/*
	  Start I2C
	*/

	start_i2c(I2C_ADDRESS, 20, i2c_callback);

	/* Then... */
	for (;;)
		;

	return 0;
}

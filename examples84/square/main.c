/*
  main.c
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2c.h"

#define I2C_ADDRESS 7

#define MAGIC   0xbacd
#define PROJECT 0x0004
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
	uint16_t ocr1n;

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
			ob[obi++] = OCR1A & 0xff;
			ob[obi++] = (OCR1A & 0xff00) >> 8;
			break;
		case 0x83:
			ocr1n  = ((unsigned short)(ib[ibi++]));
			ocr1n |= ((unsigned short)(ib[ibi++]) << 8);
			OCR1A = ocr1n;
			break;
		case 0x04:
			ob[obi++] = OCR1B & 0xff;
			ob[obi++] = (OCR1B & 0xff00) >> 8;
			break;
		case 0x84:
			ocr1n  = ((unsigned short)(ib[ibi++]));
			ocr1n |= ((unsigned short)(ib[ibi++]) << 8);
			OCR1B = ocr1n;
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

	/* Make pin 8 (PA5 -- OC1B) an output. */
	DDRA |= _BV(PA5);

	TCCR1A =
		/* WGM11:10 = 0b11 */
		_BV(WGM10) | _BV(WGM11) |
		/*  */
		_BV(COM1B1);

	TCCR1B =
		/* WGM13:12 = 0b11 */
		_BV(WGM13) | _BV(WGM12) |
		/* CLKio No Prescale */
		_BV(CS10);

	OCR1A = 32768;
	OCR1B = 16384;

	/*
	  Start I2C - Use Timer0 to Check for I2C Messages
	*/

	start_i2c(I2C_ADDRESS, i2c_callback);

	/*
	  Then... wait for messages.
	*/
	for (;;)
		usi_twi_check();

	return 0;
}

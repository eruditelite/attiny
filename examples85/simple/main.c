/*
  main.c
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>

#include "tick.h"
#include "i2c.h"

#define I2C_ADDRESS 7

#define MAGIC   0xbacd
#define PROJECT 0x0002
#define VERSION 0x0001

/*
  Check for I2C Messages...
*/

ISR(TIM0_COMPA_vect)
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
	static uint8_t dummy1 = 0x11;
	static uint16_t dummy2 = 0x2222;
	static uint32_t dummy4 = 0x44444444;

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
			/* Return dummy1. */
			ob[obi++] = dummy1;
			break;
		case 0x83:
			/* Set dummy1. */
			dummy1 = ib[ibi++];
			break;
		case 0x04:
			/* Return dummy2. */
			ob[obi++] = (dummy2 & 0xff00) >> 8;
			ob[obi++] = dummy2 & 0xff;
			break;
		case 0x84:
			/* Set dummy2. */
			dummy2 = ((unsigned short)(ib[ibi++]) << 8);
			dummy2 |= ((unsigned short)(ib[ibi++]));
			break;
		case 0x05:
			/* Return dummy4. */
			ob[obi++] = (dummy4 & 0xff000000) >> 24;
			ob[obi++] = (dummy4 & 0xff0000) >> 16;
			ob[obi++] = (dummy4 & 0xff00) >> 8;
			ob[obi++] = dummy4 & 0xff;
			break;
		case 0x85:
			/* Set dummy4. */
			dummy4 = ((unsigned long)(ib[ibi++]) << 24);
			dummy4 |= ((unsigned long)(ib[ibi++]) << 16);
			dummy4 |= ((unsigned long)(ib[ibi++]) << 8);
			dummy4 |= ((unsigned long)(ib[ibi++]));
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

	/*
	  Start the Tick
	*/

	start_tick(0);

	/*
	  Start I2C - Use Timer0 to Check for I2C Messages
	*/

	start_i2c(I2C_ADDRESS, i2c_callback);

	TCCR0A = _BV(WGM01);
	TCCR0B = _BV(CS01);
	OCR0A = 20;
	TIMSK = _BV(OCIE0A);

	/* Then... */
	for (;;)
		;

	return 0;
}

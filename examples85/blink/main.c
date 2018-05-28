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

unsigned long delay[2];

void
pb3_handler(void)
{
	PORTB ^= _BV(PB3);

	return;
}

void
pb4_handler(void)
{
	PORTB ^= _BV(PB4);

	return;
}

void (*handler[2])(void) = {pb3_handler, pb4_handler};

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
	uint8_t di;
	uint32_t delay_in_ms;

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
		case 0x04:
			/* Read delay. */
			di = (ib[ibi - 1] - 0x03);
			delay_in_ms = TICKS_TO_MS(delay[di]);
			ob[obi++] = delay_in_ms & 0xff;
			ob[obi++] = (delay_in_ms & 0xff00) >> 8;
			ob[obi++] = (delay_in_ms & 0xff0000) >> 16;
			ob[obi++] = (delay_in_ms & 0xff000000) >> 24;
			break;
		case 0x83:
		case 0x84:
			/* Set the delay. */
			di = (ib[ibi - 1] - 0x83);
			delay_in_ms = ((unsigned long)(ib[ibi++]));
			delay_in_ms |= ((unsigned long)(ib[ibi++]) << 8);
			delay_in_ms |= ((unsigned long)(ib[ibi++]) << 16);
			delay_in_ms |= ((unsigned long)(ib[ibi++]) << 24);
			delay[di] = MS_TO_TICKS(delay_in_ms);

			if (0 == delay[di])
				delay[di] = 1;

			set_callback(di, 1, delay[di], handler[di]);
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

 	/* Set pins 3 and 4 to output. */
	DDRB |= (_BV(PB3) | _BV(PB4));

	/* Make both pins low to start. */
	PORTB |= ~(_BV(PB3) | _BV(PB4));

	/*
	  Add Handlers
	*/

	delay[0] = MS_TO_TICKS(1000);
	set_callback(0, 1, delay[0], handler[0]);
	delay[1] = MS_TO_TICKS(1000);
	set_callback(1, 1, delay[1], handler[1]);

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

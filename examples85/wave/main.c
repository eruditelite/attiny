/*
  main.c
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#define WAVE_SIZE 0
#define SAMPLE_RATE 2
#define WAVE_TABLE 3

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

	TIMSK = _BV(OCIE0A);

	/* timer0... interrupt to output samples */

	TCCR0A = _BV(WGM00);
	TCCR0B = _BV(WGM02) | _BV(CS00);

	/*
	  Enable Interrupts
	*/

	sei();

	/* Then... */
	for (;;)
		;

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
	OCR0A = eeprom_read_byte((uint8_t *)SAMPLE_RATE);
	TIMSK |= _BV(OCIE0A);
}

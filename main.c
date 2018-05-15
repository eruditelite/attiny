/*
  main.c
*/

#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include <usitwislave.h>

#define I2C_ADDRESS 8

#ifdef SIM
#include <simavr/sim/avr/avr_mcu_section.h>

AVR_MCU(8000000, "attiny85");
AVR_MCU_VCD_FILE("blinky_sim.vcd", 1000);

const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {
	{
		AVR_MCU_VCD_SYMBOL("PORTB3"),
		.mask = (1 << PORTB3),
		.what = (void*)&PORTB,
	},
	{
		AVR_MCU_VCD_SYMBOL("PORTB4"),
		.mask = (1 << PORTB4),
		.what = (void*)&PORTB,
	}
};
#endif

void
my_data_callback(uint8_t input_buffer_length,
		 const uint8_t *input_buffer,
		 uint8_t *output_buffer_length,
		 uint8_t *output_buffer)
{
	int i;

	PORTB ^= (1 << PORTB4);

	for (i = 0; i < input_buffer_length; ++i) {
		output_buffer[i] = input_buffer[i];
	}

	*output_buffer_length = input_buffer_length;

	return;
}

void
my_idle_callback(void)
{
	PORTB ^= (1 << PORTB3);

	return;
}

int
main(void)
{
	/* Set pins 2 and 3 to output. */
	DDRB |= (1 << PORTB3) | (1 << PORTB4);

	/* Make pins low to start. */
	PORTB &= ~((1 << PORTB3) | (1 << PORTB4));

	/* blink 3 times */
	PORTB ^= (1 << PORTB3);
	_delay_ms(100);
	PORTB ^= (1 << PORTB3);
	_delay_ms(100);
	PORTB ^= (1 << PORTB3);
	_delay_ms(100);
	PORTB ^= (1 << PORTB3);
	_delay_ms(100);
	PORTB ^= (1 << PORTB3);
	_delay_ms(100);
	PORTB ^= (1 << PORTB3);

	/* Initialize USITWISLAVE */
	usi_twi_slave(I2C_ADDRESS,
		      0,
		      my_data_callback,
		      my_idle_callback);

	/* blink forever */
	for (;;) {
		_delay_ms(1000);
		PORTB ^= (1 << PORTB3);
	}

	return 0;
}

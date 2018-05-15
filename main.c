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

	for (i = 0; i < input_buffer_length; ++i) {
		switch (input_buffer[i]) {
		case 0xff:
			/* Magic */
			output_buffer[0] = 0xba;
			output_buffer[1] = 0xcd;
			*output_buffer_length = 2;
			break;
		case 0xfe:
			/* Project and Version */
			output_buffer[0] = 0x01; /* project */
			output_buffer[1] = 0x01; /* version */
			*output_buffer_length = 2;
			break;
		default:
			break;
		}
	}

	return;
}

void
my_idle_callback(void)
{
	return;
}

int
main(void)
{
	/* Initialize USITWISLAVE */
	usi_twi_slave(I2C_ADDRESS,
		      0,
		      my_data_callback,
		      my_idle_callback);

	return 0;
}

/*
  main.c
*/

#include "attiny85_wr.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <usitwislave.h>

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

int
main(void)
{
	/* Start counting time... */
	time_init();

	/* Initialize USITWISLAVE */
	usi_twi_slave(I2C_ADDRESS, 0, data_callback, idle_callback);

 	/* Set pin 2 to output. */
	DDRB |= (1 << PORTB4);

	/* Make pin low to start. */
	PORTB &= ~(1 << PORTB4);

	for (;;) {
		PORTB ^= (1 << PORTB4);
		_delay_ms(500);
	}

	return 0;
}

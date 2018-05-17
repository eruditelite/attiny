################################################################################
#
# Makefile for "attiny85_wr".
#
# Basic example of using attiny85 with registers accessible via I2C.
#
################################################################################

MCU = attiny85
AVRDUDEMCU = t85
USITWISLAVE = ../usitwislave
AVR_CC = avr-gcc
AVR_CFLAGS = -Os -Wall -mcall-prologues -mmcu=$(MCU) -I$(USITWISLAVE)
AVR_SIM_CFLAGS = $(AVR_CFLAGS) -g -DSIM -I~/apps/simavr
AVR_OBJ2HEX = avr-objcopy
RESETPIN = 22
AVRDUDE = avrdude
AVRDUDE_OPTIONS = -p $(AVRDUDEMCU) -P /dev/spidev0.0 -c linuxspi -b 10000

all : attiny85_wr attiny85_wr.hex access

access : access.c
	gcc -O3 -Wall -o $@ $<

attiny85_wr.hex : attiny85_wr
	$(AVR_OBJ2HEX) -R .eeprom -O ihex $< $@

attiny85_wr : main.o callbacks.o time.o work.o usitwislave.o
	$(AVR_CC) $(AVR_CFLAGS) -o $@ $^

usitwislave.o : $(USITWISLAVE)/usitwislave.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

main.o : main.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

callbacks.o : callbacks.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

time.o : time.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

work.o : work.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

cscope : main.c callbacks.c time.c $(USITWISLAVE)/usitwislave.c
	@$(AVR_CC) $(AVR_CFLAGS) -M $^ \
		| sed -e 's/[\\ ]/\n/g' \
		| sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' \
		| sort -u >cscope.files
	@cscope -b

install : attiny85_wr.hex
	sudo gpio -g mode $(RESETPIN) out
	sudo gpio -g write $(RESETPIN) 0
	sudo $(AVRDUDE) $(AVRDUDE_OPTIONS) -U flash:w:$<
	sudo gpio -g write $(RESETPIN) 1

reset :
	sudo gpio -g mode $(RESETPIN) out
	sudo gpio -g write $(RESETPIN) 0
	sudo gpio -g write $(RESETPIN) 1

clean :
	rm -f *~ *.hex *.d *.o *.vcd attiny85_wr cscope.* access

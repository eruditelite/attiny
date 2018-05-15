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
CC = avr-gcc
CFLAGS = -Os -Wall -mcall-prologues -mmcu=$(MCU) -I$(USITWISLAVE)
SIM_CFLAGS = -g -Os -Wall -mcall-prologues -mmcu=$(MCU) -DSIM -I~/apps/simavr
OBJ2HEX = avr-objcopy
RESETPIN = 22
AVRDUDE = avrdude
AVRDUDE_OPTIONS = -p $(AVRDUDEMCU) -P /dev/spidev0.0 -c linuxspi -b 10000

all : attiny85_wr attiny85_wr.hex access

access : access.c
	gcc -o access access.c

attiny85_wr.hex : attiny85_wr
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

attiny85_wr : main.o usitwislave.o
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c \
	$(USITWISLAVE)/usitwislave_devices.h $(USITWISLAVE)/usitwislave.h
	$(CC) $(CFLAGS) -c -o $@ $<

usitwislave.o : $(USITWISLAVE)/usitwislave.c \
	$(USITWISLAVE)/usitwislave_devices.h $(USITWISLAVE)/usitwislave.h
	$(CC) $(CFLAGS) -c -o $@ $<

cscope.files :
	$(CC) $(CFLAGS) -M main.c | sed -e 's/[\\ ]/\n/g' | sed -e '/^$/d' -e '/\.o:[ \t]*$/d' >cscope.files
	$(CC) $(CFLAGS) -M $(USITWISLAVE)/usitwislave.c | sed -e 's/[\\ ]/\n/g' | sed -e '/^$/d' -e '/\.o:[ \t]*$/d' >>cscope.files

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
	rm -f *.hex *.o *.vcd attiny85_wr cscope.* access

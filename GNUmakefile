################################################################################
#
# Makefile for "attiny85_wr".
#
# Basic example of using attiny85 with registers accessible via I2C.
#
################################################################################

#MCU = attiny85
#AVRDUDEMCU = t85

MCU = attiny84
AVRDUDEMCU = t84

RESETPIN = 22
AVRDUDE = avrdude
AVRDUDE_OPTIONS = -p $(AVRDUDEMCU) -P /dev/spidev0.0 -c linuxspi -b 10000

USITWI = ../usitwislave
ATTINY = .
AVR_CC = avr-gcc
AVR_CFLAGS = -Os -Wall -mcall-prologues -mmcu=$(MCU) -I$(ATTINY) -I$(USITWI)
AVR_OBJ2HEX = avr-objcopy

all : attiny attiny.hex access

access : access.c
	gcc -O3 -Wall -o $@ $<

attiny.hex : attiny
	$(AVR_OBJ2HEX) -R .eeprom -O ihex $< $@

attiny : main.o attiny.o usitwislave.o
	$(AVR_CC) $(AVR_CFLAGS) -o $@ $^

usitwislave.o : $(USITWI)/usitwislave.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

main.o : $(ATTINY)/main.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

attiny.o : attiny.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

cscope : $(ATTINY)/main.c attiny.c $(USITWI)/usitwislave.c
	@$(AVR_CC) $(AVR_CFLAGS) -M $^ \
		| sed -e 's/[\\ ]/\n/g' \
		| sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' \
		| sort -u >cscope.files
	@cscope -b

install : attiny.hex
	sudo gpio -g mode $(RESETPIN) out
	sudo gpio -g write $(RESETPIN) 0
	sudo $(AVRDUDE) $(AVRDUDE_OPTIONS) -U flash:w:$<
	sudo gpio -g write $(RESETPIN) 1

fuse :
	sudo gpio -g mode $(RESETPIN) out
	sudo gpio -g write $(RESETPIN) 0
	sudo $(AVRDUDE) $(AVRDUDE_OPTIONS) \
		-U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
	sudo gpio -g write $(RESETPIN) 1

reset :
	sudo gpio -g mode $(RESETPIN) out
	sudo gpio -g write $(RESETPIN) 0
	sudo gpio -g write $(RESETPIN) 1

clean :
	rm -f *~ *.hex *.d *.o *.vcd attiny cscope.* access

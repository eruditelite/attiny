################################################################################
################################################################################
#
# Makefile for "attiny".
#
# Basic examples of using attiny84/attiny85 with registers accessible via I2C.
#
################################################################################
################################################################################

###################################################
## Setup for attiny84 on spidev0.0 with I2C id 4 ##
###################################################

MCU = attiny84
AVRDUDEMCU = t84
SPIDEV = /dev/spidev0.0

###################################################
## Setup for attiny85 on spidev1.0 with I2C id 5 ##
###################################################

#MCU = attiny85
#AVRDUDEMCU = t85
#SPIDEV = /dev/spidev1.0

##################################################
## Macros to switch PI modes and reset the AVRs ##
##################################################

define SWITCH_PI_TO_SPI
gpio -g mode 2 in
gpio -g mode 3 in
gpio -g mode 9 alt0
gpio -g mode 10 alt0
gpio -g mode 11 alt0
gpio -g mode 19 alt4
gpio -g mode 20 alt4
gpio -g mode 21 alt4
endef

define SWITCH_PI_TO_I2C
gpio -g mode 9 in
gpio -g mode 10 in
gpio -g mode 11 in
gpio -g mode 19 in
gpio -g mode 20 in
gpio -g mode 21 in
gpio -g mode 2 alt0
gpio -g mode 3 alt0
endef

define SET_RESET
gpio -g mode 22 out
gpio -g write 22 0
endef

define CLEAR_RESET
gpio -g mode 22 out
gpio -g write 22 1
gpio -g mode 22 in
endef

###############################
## Build options and Targets ##
###############################

USITWI = ../usitwislave
ATTINY = .
AVR_CC = avr-gcc
AVR_CFLAGS = -Os -Wall -mcall-prologues -mmcu=$(MCU) -I$(ATTINY) -I$(USITWI)
AVR_OBJ2HEX = avr-objcopy
AVRDUDE = avrdude
AVRDUDE_OPTIONS = -p $(AVRDUDEMCU) -P $(SPIDEV) -c linuxspi -b 10000

.PHONY : all cscope install fuse reset clean

all : attiny attiny.hex access

access : access.c
	gcc -Wall -pthread -o $@ $< -lpigpiod_if2 -lrt

attiny.hex : attiny
	$(AVR_OBJ2HEX) -R .eeprom -O ihex $< $@

attiny : main.o attiny.o usitwislave.o
	$(AVR_CC) $(AVR_CFLAGS) -o $@ $^
	avr-size -C --mcu $(MCU) $@

usitwislave.o : $(USITWI)/usitwislave.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

main.o : $(ATTINY)/main.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

attiny.o : attiny.c
	$(AVR_CC) $(AVR_CFLAGS) -c -o $@ $<

cscope : $(ATTINY)/main.c attiny.c $(USITWI)/usitwislave.c
	$(AVR_CC) $(AVR_CFLAGS) -M $^ \
		| sed -e 's/[\\ ]/\n/g' \
		| sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' \
		| sort -u >cscope.files
	cscope -b

install : attiny.hex
	@$(call SWITCH_PI_TO_SPI)
	@$(call SET_RESET)
	sudo $(AVRDUDE) $(AVRDUDE_OPTIONS) -U flash:w:$<
	@$(call CLEAR_RESET)
	@$(call SWITCH_PI_TO_I2C)

fuse :
	@$(call SWITCH_PI_TO_SPI)
	@$(call SET_RESET)
	sudo $(AVRDUDE) $(AVRDUDE_OPTIONS) \
		-U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
	@$(call CLEAR_RESET)
	@$(call SWITCH_PI_TO_I2C)

reset :
	@$(call SET_RESET)
	@$(call CLEAR_RESET)
	@$(call SWITCH_PI_TO_I2C)

clean :
	@rm -f *~ *.hex *.d *.o *.vcd attiny cscope.* access

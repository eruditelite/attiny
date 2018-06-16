# attiny -- ATTiny84/ATTiny85 Examples using the Raspberry Pi #

## Overview ##

Most of the ATTiny examples seem to be based on the Arduino.  As I
wanted a simple example using the Raspberry Pi (the reason for all of
this is controlling telescopes using lin_guider etc.), I decided to
write this all down so I could remember it later!

## Basic Functionality ##

At the top, is a template that works on either the ATTiny84 or
ATTiny85.  It includes a way to use i2c, and a system tick, but not
much else.  For inputs, outputs, interrupts, etc. see the examples.

For the test setup, a Raspberry Pi is used to program the ATTinys and
read/write "registers.  Since the test board will have two parts (one
ATTiny84 and one ATTiny85), separate SPI and I2C interfaces are used
for each.  The EEPROM I2C interface (pins 0 and 1) and SPI0 (pins 9,
10, and 11) are used for the ATTiny84.  For the ATTiny85, I2C (pins 3
and 3) and SPI1 (pins 19, 20, and 21) are used.  Note that the EEPROM
clock and data pins do not include a pull up resitor!  A 1K resitor is
include from each to +3.3V.

BCM 22 is used as a reset, connected to both ATTinys.

## Examples ##

### ATTiny 84 Simple ###

### ATTiny 84 Blink ###

### ATTiny 84 Square ###

### ATTiny 84 Wave ###

### ATTiny 84 Simple ###

### ATTiny 85 Blink ###

### ATTiny 85 Square ###

### ATTiny 85 Wave ###

### ATTiny 85 ADC ###

### ATTiny 85 Activity ###


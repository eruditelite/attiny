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

In some cases, multiple pins from the Raspberry Pi connect to a single
pin on the ATTiny.  All pins related to the function not being used
(I2C or SPI) should be tristated.  In this document, the BCM numers
will be used and the 'gpio' command will be used with the '-g' option.
Details are available in makefile.attiny84 and makefile.attiny85.
Both of those makefiles include macros to switch the Raspberry
Pi/ATTiny connection to SPI mode or to I2C mode.

## Examples ##

### ATTiny 84 Simple ###

### ATTiny 84 Blink ###

### ATTiny 84 Square ###

### ATTiny 84 Wave ###

### ATTiny 84 Simple ###

### ATTiny 85 Blink ###

### ATTiny 85 Square ###

Square wave output on PB1.  OCR1A is the "percentage on" (0...255);
the initial value is 127.  Use a low pass filter to smooth the output.
Resistor and capacitor values will depend on the load etc.

![Low Pass](images/lowpassfordc.png)

### ATTiny 85 Wave ###

This example uses timer/counter 1 for PWM output on PB4 and
timer/counter 0 as a trigger to change the sample.  The samples are
stored in eeprom.  An example of generating sample sets is provited by
wavegen.c (after compiling, see ./wavegen -h for a description).
Writing the sample to eeprom is handled by the 'eeprom' target in
makefile.attiny.  First a binary is created by wavegen, then the make
target converts the binary to Intel hex and writes it to the eeprom
using avrdude.

As the interrupts from timer/counter 0 are fairly fast, I2C is not
supported.

Use a low pass filter on the output as follows.

![Low Pass](images/lowpassforwave.png)

### ATTiny 85 ADC ###

### ATTiny 85 Activity ###


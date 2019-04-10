#!/bin/sh

# Disable SPI Buffer (1 = disable, 0 = enable)
#
echo "--> Disable the SPI Buffers"
gpio -g mode 23 out		# Clock and MOSI
gpio -g write 23 1
gpio -g mode 14 out		# MISO from ATTiny84
gpio -g write 14 1
gpio -g mode 15 out		# MISO from ATTiny85
gpio -g write 15 1

# ATTiny84 Reset (0 = disable, 1 = enable)
#
echo "--> Set Up the Reset Pin and Enable the ATTiny84"
gpio -g mode 27 out
gpio -g write 27 0
sleep 1
gpio -g write 27 1

# ATTiny85 Reset (0 = disable, 1 = enable)
echo "--> Set Up the Reset Pin and Enable the ATTiny85"
gpio -g mode 4 out
gpio -g write 4 0
sleep 1
gpio -g write 4 1

# Enable SPI
#
echo "--> Enable SPI"
gpio -g mode 9 alt0
gpio -g mode 10 alt0
gpio -g mode 11 alt0

# Enable I2C
#
echo "--> Enable I2C"
gpio -g mode 2 alt0
gpio -g mode 3 alt0

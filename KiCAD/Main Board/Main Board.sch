EESchema Schematic File Version 4
LIBS:Main Board-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "15 nov 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+5V #PWR01
U 1 1 580C1B61
P 2450 2700
F 0 "#PWR01" H 2450 2550 50  0001 C CNN
F 1 "+5V" H 2450 2840 50  0000 C CNN
F 2 "" H 2450 2700 50  0000 C CNN
F 3 "" H 2450 2700 50  0000 C CNN
	1    2450 2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2450 2700 2450 2850
Wire Wire Line
	2450 2850 2650 2850
Wire Wire Line
	2450 2950 2650 2950
Connection ~ 2450 2850
$Comp
L power:GND #PWR02
U 1 1 580C1D11
P 2550 4900
F 0 "#PWR02" H 2550 4650 50  0001 C CNN
F 1 "GND" H 2550 4750 50  0000 C CNN
F 2 "" H 2550 4900 50  0000 C CNN
F 3 "" H 2550 4900 50  0000 C CNN
	1    2550 4900
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 580C1E01
P 3250 4900
F 0 "#PWR03" H 3250 4650 50  0001 C CNN
F 1 "GND" H 3250 4750 50  0000 C CNN
F 2 "" H 3250 4900 50  0000 C CNN
F 3 "" H 3250 4900 50  0000 C CNN
	1    3250 4900
	-1   0    0    -1  
$EndComp
Connection ~ 3350 2850
Wire Wire Line
	3350 3650 3150 3650
Wire Wire Line
	3350 2850 3150 2850
Wire Wire Line
	3350 2700 3350 2850
$Comp
L power:+3.3V #PWR04
U 1 1 580C1BC1
P 3350 2700
F 0 "#PWR04" H 3350 2550 50  0001 C CNN
F 1 "+3.3V" H 3350 2840 50  0000 C CNN
F 2 "" H 3350 2700 50  0000 C CNN
F 3 "" H 3350 2700 50  0000 C CNN
	1    3350 2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3250 3250 3150 3250
Wire Wire Line
	4300 3150 3150 3150
Wire Wire Line
	3150 3350 4300 3350
Wire Wire Line
	4300 3450 3150 3450
Wire Wire Line
	4300 4250 3150 4250
Wire Wire Line
	4300 4350 3150 4350
Wire Wire Line
	3150 4450 4300 4450
Wire Wire Line
	4300 4650 3150 4650
Wire Wire Line
	2650 4550 1600 4550
Wire Wire Line
	2650 4050 1600 4050
Wire Wire Line
	2650 3850 1600 3850
Wire Wire Line
	2650 3950 1600 3950
Wire Wire Line
	2650 3550 1600 3550
Wire Wire Line
	2650 3650 1600 3650
Wire Wire Line
	2650 3250 1600 3250
Wire Wire Line
	2650 3350 1600 3350
Wire Wire Line
	2650 4350 1600 4350
Text Label 4300 2950 2    50   ~ 0
GPIO2(SDA1)
Text Label 4300 3050 2    50   ~ 0
GPIO3(SCL1)
Text Label 4300 3150 2    50   ~ 0
GPIO4(GCLK)
Text Label 4300 3350 2    50   ~ 0
GPIO17(GEN0)
Text Label 4300 3450 2    50   ~ 0
GPIO27(GEN2)
Text Label 4300 3550 2    50   ~ 0
GPIO22(GEN3)
Text Label 4300 3750 2    50   ~ 0
GPIO10(SPI0_MOSI)
Text Label 4300 3850 2    50   ~ 0
GPIO9(SPI0_MISO)
Text Label 4300 3950 2    50   ~ 0
GPIO11(SPI0_SCK)
Text Label 4300 4150 2    50   ~ 0
ID_SD
Text Label 4300 4250 2    50   ~ 0
GPIO5
Text Label 4300 4350 2    50   ~ 0
GPIO6
Text Label 4300 4450 2    50   ~ 0
GPIO13(PWM1)
Text Label 4300 4550 2    50   ~ 0
GPIO19(SPI1_MISO)
Text Label 4300 4650 2    50   ~ 0
GPIO26
Text Label 1600 4550 0    50   ~ 0
GPIO16
Text Label 1600 4350 0    50   ~ 0
GPIO12(PWM0)
Text Label 1600 4150 0    50   ~ 0
ID_SC
Text Label 1600 4050 0    50   ~ 0
GPIO7(SPI1_CE_N)
Text Label 1600 3950 0    50   ~ 0
GPIO8(SPI0_CE_N)
Text Label 1600 3850 0    50   ~ 0
GPIO25(GEN6)
Text Label 1600 3650 0    50   ~ 0
GPIO24(GEN5)
Text Label 1600 3550 0    50   ~ 0
GPIO23(GEN4)
Text Label 1600 3350 0    50   ~ 0
GPIO18(GEN1)(PWM0)
Text Label 1600 3250 0    50   ~ 0
GPIO15(RXD0)
Wire Wire Line
	2550 3050 2650 3050
Text Notes 650  7600 0    50   ~ 0
ID_SD and ID_SC PINS:\nThese pins are reserved for HAT ID EEPROM.\n\nAt boot time this I2C interface will be\ninterrogated to look for an EEPROM\nthat identifes the attached board and\nallows automagic setup of the GPIOs\n(and optionally, Linux drivers).\n\nDO NOT USE these pins for anything other\nthan attaching an I2C ID EEPROM. Leave\nunconnected if ID EEPROM not required.
$Comp
L Main-Board-rescue:Mounting_Hole-Mechanical-ATTiny-Examples-rescue MK1
U 1 1 5834FB2E
P 3000 7200
F 0 "MK1" H 3100 7246 50  0000 L CNN
F 1 "M2.5" H 3100 7155 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 3000 7200 60  0001 C CNN
F 3 "" H 3000 7200 60  0001 C CNN
	1    3000 7200
	1    0    0    -1  
$EndComp
$Comp
L Main-Board-rescue:Mounting_Hole-Mechanical-ATTiny-Examples-rescue MK3
U 1 1 5834FBEF
P 3450 7200
F 0 "MK3" H 3550 7246 50  0000 L CNN
F 1 "M2.5" H 3550 7155 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 3450 7200 60  0001 C CNN
F 3 "" H 3450 7200 60  0001 C CNN
	1    3450 7200
	1    0    0    -1  
$EndComp
$Comp
L Main-Board-rescue:Mounting_Hole-Mechanical-ATTiny-Examples-rescue MK2
U 1 1 5834FC19
P 3000 7400
F 0 "MK2" H 3100 7446 50  0000 L CNN
F 1 "M2.5" H 3100 7355 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 3000 7400 60  0001 C CNN
F 3 "" H 3000 7400 60  0001 C CNN
	1    3000 7400
	1    0    0    -1  
$EndComp
$Comp
L Main-Board-rescue:Mounting_Hole-Mechanical-ATTiny-Examples-rescue MK4
U 1 1 5834FC4F
P 3450 7400
F 0 "MK4" H 3550 7446 50  0000 L CNN
F 1 "M2.5" H 3550 7355 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 3450 7400 60  0001 C CNN
F 3 "" H 3450 7400 60  0001 C CNN
	1    3450 7400
	1    0    0    -1  
$EndComp
Text Notes 3000 7050 0    50   ~ 0
Mounting Holes
$Comp
L Connector_Generic:Conn_02x20_Odd_Even P1
U 1 1 59AD464A
P 2950 3750
F 0 "P1" H 3000 2600 50  0000 C CNN
F 1 "Raspberry Pi" H 3000 4850 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H -1900 2800 50  0001 C CNN
F 3 "" H -1900 2800 50  0001 C CNN
	1    2950 3750
	-1   0    0    -1  
$EndComp
Text Label 1600 4750 0    50   ~ 0
GPIO21(SPI1_SCK)
Wire Wire Line
	2450 2850 2450 2950
Wire Wire Line
	3350 2850 3350 3650
$Comp
L MCU_Microchip_ATtiny:ATtiny84-20PU U1
U 1 1 5C95B743
P 6700 2150
F 0 "U1" H 6350 3150 50  0000 R CNN
F 1 "ATtiny84-20PU" H 7500 3150 50  0000 R CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6700 2150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc8006.pdf" H 6700 2150 50  0001 C CNN
	1    6700 2150
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U2
U 1 1 5C95B8B2
P 7200 5400
F 0 "U2" H 6800 4700 50  0000 R CNN
F 1 "ATtiny85-20PU" H 8000 4700 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7200 5400 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 7200 5400 50  0001 C CNN
	1    7200 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 5C95BA78
P 6700 1250
F 0 "#PWR05" H 6700 1100 50  0001 C CNN
F 1 "+3.3V" H 6715 1423 50  0000 C CNN
F 2 "" H 6700 1250 50  0001 C CNN
F 3 "" H 6700 1250 50  0001 C CNN
	1    6700 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5C95BBAF
P 6700 3050
F 0 "#PWR06" H 6700 2800 50  0001 C CNN
F 1 "GND" H 6700 2900 50  0000 C CNN
F 2 "" H 6700 3050 50  0000 C CNN
F 3 "" H 6700 3050 50  0000 C CNN
	1    6700 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5C95BBF9
P 7200 6000
F 0 "#PWR08" H 7200 5750 50  0001 C CNN
F 1 "GND" H 7200 5850 50  0000 C CNN
F 2 "" H 7200 6000 50  0000 C CNN
F 3 "" H 7200 6000 50  0000 C CNN
	1    7200 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2750 7300 2750
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5C9685F6
P 5900 4900
F 0 "J3" H 5900 5150 50  0000 C CNN
F 1 "ATtiny85 I2c/SPI Debug" H 5900 4650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5900 4900 50  0001 C CNN
F 3 "~" H 5900 4900 50  0001 C CNN
	1    5900 4900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1350 4150 1350 5200
Wire Wire Line
	1350 4150 2650 4150
Wire Wire Line
	3150 3950 5100 3950
Connection ~ 5100 3950
Wire Wire Line
	5100 3950 5100 3400
Wire Wire Line
	5000 3850 5000 3300
Wire Wire Line
	3150 3850 5000 3850
Wire Wire Line
	5200 4150 5200 3750
Wire Wire Line
	5200 3500 5700 3500
Wire Wire Line
	3150 4150 5200 4150
Wire Wire Line
	3150 3750 5200 3750
Connection ~ 5200 3750
Wire Wire Line
	5200 3750 5200 3500
Wire Wire Line
	7400 2750 7400 3600
Wire Wire Line
	3150 3550 4300 3550
Wire Wire Line
	4300 3600 4300 3550
Wire Wire Line
	3150 3050 4500 3050
Text Label 1600 4650 0    50   ~ 0
GPIO20(SPI1_MOSI)
Wire Wire Line
	1250 4750 2650 4750
Wire Wire Line
	2650 4650 1150 4650
Wire Wire Line
	3150 2950 4600 2950
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J1
U 1 1 5C99E63B
P 9700 3400
F 0 "J1" H 9750 4017 50  0000 C CNN
F 1 "Daughter Board Connector" H 9750 3926 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 9700 3400 50  0001 C CNN
F 3 "~" H 9700 3400 50  0001 C CNN
	1    9700 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1550 8850 1550
Wire Wire Line
	7300 1650 8800 1650
Wire Wire Line
	7300 1750 8750 1750
Wire Wire Line
	7300 1850 8700 1850
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5C9686BC
P 4600 2350
F 0 "J2" H 4550 2100 50  0000 L CNN
F 1 "ATtiny84 I2C/SPI Debug" H 4850 2350 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4600 2350 50  0001 C CNN
F 3 "~" H 4600 2350 50  0001 C CNN
	1    4600 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7300 2250 8500 2250
Wire Wire Line
	7300 1950 7600 1950
Wire Wire Line
	7300 2050 7500 2050
Wire Wire Line
	7300 2150 7700 2150
Wire Wire Line
	5000 3300 5600 3300
Wire Wire Line
	5100 3400 5500 3400
Wire Wire Line
	7500 2050 7500 3300
Connection ~ 7500 2050
Wire Wire Line
	7500 2050 8600 2050
Wire Wire Line
	7600 1950 7600 3400
Connection ~ 7600 1950
Wire Wire Line
	7600 1950 8650 1950
Wire Wire Line
	7700 2150 7700 3500
Connection ~ 7700 2150
Wire Wire Line
	7700 2150 8550 2150
NoConn ~ 3150 3350
NoConn ~ 3150 3450
NoConn ~ 3150 4250
NoConn ~ 3150 4350
NoConn ~ 3150 4450
NoConn ~ 3150 4650
NoConn ~ 2650 4550
NoConn ~ 2650 4350
NoConn ~ 2650 4050
NoConn ~ 2650 3950
NoConn ~ 2650 3850
NoConn ~ 2650 3650
NoConn ~ 2650 3550
NoConn ~ 2650 3350
NoConn ~ 2650 3250
NoConn ~ 2650 3150
Text Label 1600 3150 0    50   ~ 0
GPIO14(TXD0)
Wire Wire Line
	2650 3150 1600 3150
NoConn ~ 3150 3150
$Comp
L Device:R R1
U 1 1 5CB34A48
P 4900 1800
F 0 "R1" H 4950 1850 50  0000 L CNN
F 1 "1K" H 4950 1750 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4830 1800 50  0001 C CNN
F 3 "~" H 4900 1800 50  0001 C CNN
	1    4900 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR012
U 1 1 5CB5E90B
P 5100 1400
F 0 "#PWR012" H 5100 1250 50  0001 C CNN
F 1 "+3.3V" H 5115 1573 50  0000 C CNN
F 2 "" H 5100 1400 50  0001 C CNN
F 3 "" H 5100 1400 50  0001 C CNN
	1    5100 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2450 5500 3400
Connection ~ 5500 3400
Wire Wire Line
	5500 3400 7600 3400
Wire Wire Line
	5600 2350 5600 3300
Connection ~ 5600 3300
Wire Wire Line
	5600 3300 7500 3300
$Comp
L Device:R R2
U 1 1 5CB34ACD
P 5300 1800
F 0 "R2" H 5370 1846 50  0000 L CNN
F 1 "1K" H 5370 1755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5230 1800 50  0001 C CNN
F 3 "~" H 5300 1800 50  0001 C CNN
	1    5300 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2250 4900 2250
Wire Wire Line
	4800 2350 5600 2350
Wire Wire Line
	4800 2450 5300 2450
Wire Wire Line
	4900 1950 4900 2250
Connection ~ 4900 2250
Wire Wire Line
	4900 2250 5700 2250
Wire Wire Line
	5300 1950 5300 2450
Connection ~ 5300 2450
Wire Wire Line
	5300 2450 5500 2450
Wire Wire Line
	4900 1650 4900 1600
Wire Wire Line
	4900 1600 5100 1600
Wire Wire Line
	5300 1600 5300 1650
Wire Wire Line
	5100 1400 5100 1600
Connection ~ 5100 1600
Wire Wire Line
	5100 1600 5300 1600
$Comp
L power:+3.3V #PWR09
U 1 1 5CC0EA70
P 7200 4800
F 0 "#PWR09" H 7200 4650 50  0001 C CNN
F 1 "+3.3V" H 7215 4973 50  0000 C CNN
F 2 "" H 7200 4800 50  0001 C CNN
F 3 "" H 7200 4800 50  0001 C CNN
	1    7200 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 5200 5100 5200
Wire Wire Line
	5100 5200 5100 3950
Wire Wire Line
	1250 4750 1250 5300
Wire Wire Line
	1250 5300 4500 5300
Wire Wire Line
	5200 5300 5200 4250
Wire Wire Line
	5200 4250 6300 4250
Wire Wire Line
	8200 4250 8200 5300
Wire Wire Line
	8200 5300 7800 5300
Wire Wire Line
	4500 3050 4500 5300
Connection ~ 4500 5300
Wire Wire Line
	4500 5300 5200 5300
Wire Wire Line
	1150 4650 1150 5400
Wire Wire Line
	1150 5400 4600 5400
Wire Wire Line
	5300 4350 6500 4350
Wire Wire Line
	5300 4350 5300 5400
Wire Wire Line
	8100 4350 8100 5100
Wire Wire Line
	8100 5100 7800 5100
Connection ~ 4600 5400
Wire Wire Line
	4600 5400 5300 5400
Wire Wire Line
	4600 2950 4600 5400
Wire Wire Line
	3150 4550 5400 4550
Wire Wire Line
	5400 4550 5400 4450
Wire Wire Line
	5400 4450 6400 4450
Wire Wire Line
	8000 4450 8000 5200
Wire Wire Line
	8000 5200 7800 5200
Wire Wire Line
	6400 4450 6400 4900
Wire Wire Line
	6400 4900 6100 4900
Connection ~ 6400 4450
Wire Wire Line
	6400 4450 8000 4450
Wire Wire Line
	6100 4800 6300 4800
Wire Wire Line
	6300 4800 6300 4250
Connection ~ 6300 4250
Wire Wire Line
	6300 4250 8200 4250
Wire Wire Line
	6100 5000 6500 5000
Wire Wire Line
	6500 5000 6500 4350
Connection ~ 6500 4350
Wire Wire Line
	6500 4350 8100 4350
Wire Wire Line
	8850 1550 8850 3800
Wire Wire Line
	8850 3800 9500 3800
Wire Wire Line
	8800 1650 8800 3700
Wire Wire Line
	8800 3700 9500 3700
Wire Wire Line
	8750 1750 8750 3600
Wire Wire Line
	8750 3600 9500 3600
Wire Wire Line
	8700 1850 8700 3500
Wire Wire Line
	8700 3500 9500 3500
Wire Wire Line
	8650 1950 8650 3400
Wire Wire Line
	8650 3400 9500 3400
Wire Wire Line
	8600 2050 8600 3300
Wire Wire Line
	8600 3300 9500 3300
Wire Wire Line
	8550 2150 8550 3000
Wire Wire Line
	8500 2250 8500 3100
Wire Wire Line
	8500 3100 9500 3100
Wire Wire Line
	7300 2650 8450 2650
Wire Wire Line
	9500 3000 8550 3000
Wire Wire Line
	8450 2650 8450 3200
Wire Wire Line
	8450 3200 9500 3200
Wire Wire Line
	4300 3600 7400 3600
Wire Wire Line
	5700 2250 5700 3500
Connection ~ 5700 3500
Wire Wire Line
	5700 3500 7700 3500
Connection ~ 7400 3600
Wire Wire Line
	7400 3600 7900 3600
Wire Wire Line
	7900 3600 7900 5600
Wire Wire Line
	7900 5600 7800 5600
Wire Wire Line
	7800 5400 10100 5400
Wire Wire Line
	7800 5500 10150 5500
Wire Wire Line
	10150 3700 10000 3700
Wire Wire Line
	10150 3700 10150 5500
Wire Wire Line
	10100 3800 10000 3800
Wire Wire Line
	10100 3800 10100 5400
Wire Wire Line
	8200 5300 10200 5300
Wire Wire Line
	10200 5300 10200 3600
Wire Wire Line
	10200 3600 10000 3600
Connection ~ 8200 5300
Wire Wire Line
	8000 5200 10250 5200
Wire Wire Line
	10250 5200 10250 3500
Wire Wire Line
	10250 3500 10000 3500
Connection ~ 8000 5200
Wire Wire Line
	8100 5100 10300 5100
Wire Wire Line
	10300 5100 10300 3400
Wire Wire Line
	10300 3400 10000 3400
Connection ~ 8100 5100
Wire Wire Line
	7300 2550 10400 2550
Wire Wire Line
	10400 2550 10400 3200
Wire Wire Line
	10400 3200 10000 3200
Wire Wire Line
	10450 3300 10000 3300
Wire Wire Line
	7300 2450 10450 2450
Wire Wire Line
	10450 2450 10450 3300
NoConn ~ 3150 4050
NoConn ~ 2650 4250
NoConn ~ 2650 3750
NoConn ~ 2650 3450
Wire Wire Line
	3250 3250 3250 4750
Wire Wire Line
	2550 3050 2550 4450
$Comp
L power:+3.3V #PWR0101
U 1 1 5CD4F49E
P 11000 3850
F 0 "#PWR0101" H 11000 3700 50  0001 C CNN
F 1 "+3.3V" H 11015 4023 50  0000 C CNN
F 2 "" H 11000 3850 50  0001 C CNN
F 3 "" H 11000 3850 50  0001 C CNN
	1    11000 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5CD4F521
P 8500 3850
F 0 "#PWR0102" H 8500 3700 50  0001 C CNN
F 1 "+5V" H 8500 3990 50  0000 C CNN
F 2 "" H 8500 3850 50  0000 C CNN
F 3 "" H 8500 3850 50  0000 C CNN
	1    8500 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10000 3900 11000 3900
Wire Wire Line
	11000 3900 11000 3850
Wire Wire Line
	8500 3850 8500 3900
Wire Wire Line
	8500 3900 9500 3900
$Comp
L power:GND #PWR0103
U 1 1 5CD5C2A5
P 11000 3200
F 0 "#PWR0103" H 11000 2950 50  0001 C CNN
F 1 "GND" H 11000 3050 50  0000 C CNN
F 2 "" H 11000 3200 50  0000 C CNN
F 3 "" H 11000 3200 50  0000 C CNN
	1    11000 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 3100 11000 3100
Wire Wire Line
	11000 3000 11000 3100
Connection ~ 11000 3100
Wire Wire Line
	11000 3100 11000 3200
Wire Wire Line
	10000 3000 11000 3000
Wire Wire Line
	2650 4450 2550 4450
Connection ~ 2550 4450
Wire Wire Line
	2550 4450 2550 4900
Wire Wire Line
	3150 4750 3250 4750
Connection ~ 3250 4750
Wire Wire Line
	3250 4750 3250 4900
$EndSCHEMATC

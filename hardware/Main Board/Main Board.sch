EESchema Schematic File Version 4
LIBS:Main Board-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
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
P 2800 1650
F 0 "#PWR01" H 2800 1500 50  0001 C CNN
F 1 "+5V" H 2800 1790 50  0000 C CNN
F 2 "" H 2800 1650 50  0000 C CNN
F 3 "" H 2800 1650 50  0000 C CNN
	1    2800 1650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2800 1900 3000 1900
$Comp
L power:GND #PWR03
U 1 1 580C1E01
P 3600 3850
F 0 "#PWR03" H 3600 3600 50  0001 C CNN
F 1 "GND" H 3600 3700 50  0000 C CNN
F 2 "" H 3600 3850 50  0000 C CNN
F 3 "" H 3600 3850 50  0000 C CNN
	1    3600 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3700 1800 3500 1800
Wire Wire Line
	3700 1650 3700 1800
$Comp
L power:+3.3V #PWR04
U 1 1 580C1BC1
P 3700 1650
F 0 "#PWR04" H 3700 1500 50  0001 C CNN
F 1 "+3.3V" H 3700 1790 50  0000 C CNN
F 2 "" H 3700 1650 50  0000 C CNN
F 3 "" H 3700 1650 50  0000 C CNN
	1    3700 1650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3000 3000 1950 3000
Wire Wire Line
	3000 2800 1950 2800
Wire Wire Line
	3000 2900 1950 2900
Wire Wire Line
	3000 2300 1950 2300
Text Label 4650 1900 2    50   ~ 0
GPIO2(SDA1)
Text Label 4650 2000 2    50   ~ 0
GPIO3(SCL1)
Text Label 4650 2100 2    50   ~ 0
GPIO4(GCLK)
Text Label 4650 2300 2    50   ~ 0
GPIO17(GEN0)
Text Label 4650 2400 2    50   ~ 0
GPIO27(GEN2)
Text Label 4650 2500 2    50   ~ 0
GPIO22(GEN3)
Text Label 4650 2700 2    50   ~ 0
GPIO10(SPI0_MOSI)
Text Label 4650 2800 2    50   ~ 0
GPIO9(SPI0_MISO)
Text Label 4650 2900 2    50   ~ 0
GPIO11(SPI0_SCK)
Text Label 4650 3100 2    50   ~ 0
ID_SD
Text Label 4650 3200 2    50   ~ 0
GPIO5
Text Label 4650 3300 2    50   ~ 0
GPIO6
Text Label 4650 3400 2    50   ~ 0
GPIO13(PWM1)
Text Label 4650 3500 2    50   ~ 0
GPIO19(SPI1_MISO)
Text Label 4650 3600 2    50   ~ 0
GPIO26
Text Label 1950 3500 0    50   ~ 0
GPIO16
Text Label 1950 3300 0    50   ~ 0
GPIO12(PWM0)
Text Label 1950 3100 0    50   ~ 0
ID_SC
Text Label 1950 3000 0    50   ~ 0
GPIO7(SPI1_CE_N)
Text Label 1950 2900 0    50   ~ 0
GPIO8(SPI0_CE_N)
Text Label 1950 2800 0    50   ~ 0
GPIO25(GEN6)
Text Label 1950 2600 0    50   ~ 0
GPIO24(GEN5)
Text Label 1950 2500 0    50   ~ 0
GPIO23(GEN4)
Text Label 1950 2300 0    50   ~ 0
GPIO18(GEN1)(PWM0)
Text Label 1950 2200 0    50   ~ 0
GPIO15(RXD0)
Text Notes 650  7600 0    50   ~ 0
ID_SD and ID_SC PINS:\nThese pins are reserved for HAT ID EEPROM.\n\nAt boot time this I2C interface will be\ninterrogated to look for an EEPROM\nthat identifes the attached board and\nallows automagic setup of the GPIOs\n(and optionally, Linux drivers).\n\nDO NOT USE these pins for anything other\nthan attaching an I2C ID EEPROM. Leave\nunconnected if ID EEPROM not required.
$Comp
L PiMounts:Mounting_Hole-Mechanical MK1
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
L PiMounts:Mounting_Hole-Mechanical MK3
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
L PiMounts:Mounting_Hole-Mechanical MK2
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
L PiMounts:Mounting_Hole-Mechanical MK4
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
P 3300 2700
F 0 "P1" H 3350 1550 50  0000 C CNN
F 1 "Raspberry Pi" H 3350 3800 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H -1550 1750 50  0001 C CNN
F 3 "" H -1550 1750 50  0001 C CNN
	1    3300 2700
	-1   0    0    -1  
$EndComp
Text Label 1950 3700 0    50   ~ 0
GPIO21(SPI1_SCK)
Text Label 1950 3600 0    50   ~ 0
GPIO20(SPI1_MOSI)
NoConn ~ 3500 3200
NoConn ~ 3500 3300
NoConn ~ 3500 3400
NoConn ~ 3500 3600
NoConn ~ 3000 3500
NoConn ~ 3000 3300
NoConn ~ 3000 3000
NoConn ~ 3000 2900
NoConn ~ 3000 2800
NoConn ~ 3000 2600
NoConn ~ 3000 2300
Text Label 1950 2100 0    50   ~ 0
GPIO14(TXD0)
NoConn ~ 3500 3000
NoConn ~ 3000 3200
NoConn ~ 3000 2700
NoConn ~ 3000 2400
Wire Wire Line
	3500 3700 3600 3700
Wire Wire Line
	3600 3700 3600 3850
NoConn ~ 3000 2000
NoConn ~ 3000 3400
NoConn ~ 3000 1800
Wire Wire Line
	2800 1650 2800 1900
$Sheet
S 8500 1500 1000 1000
U 5CACF746
F0 "ATTiny84_SubCircuit" 50
F1 "ATTiny84_SubCircuit.sch" 50
F2 "~RESET" I L 8500 1700 50 
F3 "MISO" O L 8500 2300 50 
F4 "SDA_MOSI" B L 8500 1900 50 
F5 "I2C_SPI_CLOCK" I L 8500 2100 50 
$EndSheet
$Sheet
S 8500 4000 1000 1000
U 5CBB2EC7
F0 "ATTiny85_SubCircuit" 50
F1 "ATTiny85_SubCircuit.sch" 50
F2 "~RESET" I L 8500 4800 50 
F3 "I2C_SPI_CLOCK" I L 8500 4400 50 
F4 "MISO" O L 8500 4200 50 
F5 "SDA_MOSI" B L 8500 4600 50 
$EndSheet
Wire Wire Line
	1950 2600 3000 2600
Text GLabel 4550 5600 2    50   Input ~ 0
84_PA0
Wire Wire Line
	4200 5600 4550 5600
Text GLabel 4550 5700 2    50   Input ~ 0
84_PA1
Text GLabel 4550 5800 2    50   Input ~ 0
84_PA2
Wire Wire Line
	4200 5700 4550 5700
Wire Wire Line
	4200 5800 4550 5800
Text GLabel 4550 5900 2    50   Input ~ 0
84_PA3
Text GLabel 4550 6000 2    50   Input ~ 0
84_PA4
Text GLabel 4550 6100 2    50   Input ~ 0
84_PA5
Text GLabel 4550 6200 2    50   Input ~ 0
84_PA7
Text GLabel 4550 6300 2    50   Input ~ 0
84_PA6
Wire Wire Line
	4200 5900 4550 5900
Wire Wire Line
	4200 6000 4550 6000
Wire Wire Line
	4200 6100 4550 6100
Wire Wire Line
	4200 6200 4550 6200
Wire Wire Line
	4200 6300 4550 6300
Text GLabel 3300 5700 0    50   Input ~ 0
84_PB0
Text GLabel 3300 5800 0    50   Input ~ 0
84_PB1
Text GLabel 3300 5900 0    50   Input ~ 0
84_PB3
Text GLabel 3300 6000 0    50   Input ~ 0
84_PB2
Wire Wire Line
	3300 5700 3700 5700
Wire Wire Line
	3300 5800 3700 5800
Wire Wire Line
	3300 5900 3700 5900
Wire Wire Line
	3300 6000 3700 6000
Text GLabel 3300 6100 0    50   Input ~ 0
85_PB5
Text GLabel 3300 6200 0    50   Input ~ 0
85_PB3
Text GLabel 3300 6300 0    50   Input ~ 0
85_PB4
Text GLabel 3300 6400 0    50   Input ~ 0
85_PB1
Text GLabel 3300 6500 0    50   Input ~ 0
85_PB2
Text GLabel 4550 6400 2    50   Input ~ 0
85_PB0
Wire Wire Line
	3300 6100 3700 6100
Wire Wire Line
	3300 6200 3700 6200
Wire Wire Line
	3300 6300 3700 6300
Wire Wire Line
	3300 6400 3700 6400
Wire Wire Line
	3300 6500 3700 6500
Wire Wire Line
	4200 6400 4550 6400
Wire Wire Line
	4200 6500 4350 6500
Wire Wire Line
	4350 6500 4350 6650
$Comp
L power:GND #PWR010
U 1 1 5CD1DAA5
P 4350 6650
F 0 "#PWR010" H 4350 6400 50  0001 C CNN
F 1 "GND" H 4355 6477 50  0000 C CNN
F 2 "" H 4350 6650 50  0001 C CNN
F 3 "" H 4350 6650 50  0001 C CNN
	1    4350 6650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR09
U 1 1 5CD1E4C2
P 3500 5100
F 0 "#PWR09" H 3500 4950 50  0001 C CNN
F 1 "+3.3V" H 3515 5273 50  0000 C CNN
F 2 "" H 3500 5100 50  0001 C CNN
F 3 "" H 3500 5100 50  0001 C CNN
	1    3500 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3200 4650 3200
NoConn ~ 3500 3500
NoConn ~ 3000 3700
NoConn ~ 3000 3600
NoConn ~ 3000 3100
NoConn ~ 3500 3100
Wire Wire Line
	3500 2300 4650 2300
Wire Wire Line
	3500 2500 4650 2500
$Comp
L 74hc:74HC125 U3
U 1 1 5CB024FE
P 6300 3500
F 0 "U3" H 6300 4215 50  0000 C CNN
F 1 "74HC125" H 6300 4124 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket" H 6300 3500 50  0001 C CNN
F 3 "" H 6300 3500 50  0001 C CNN
	1    6300 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2100 5000 4800
Wire Wire Line
	5000 4800 8500 4800
Wire Wire Line
	3500 2100 5000 2100
Wire Wire Line
	3500 1900 5650 1900
Wire Wire Line
	8050 2000 8050 2100
Wire Wire Line
	8050 2100 8500 2100
Wire Wire Line
	7500 1900 7500 4600
Wire Wire Line
	7500 4600 8500 4600
Connection ~ 7500 1900
Wire Wire Line
	7500 1900 8500 1900
Wire Wire Line
	7550 2000 7550 4400
Wire Wire Line
	7550 4400 8500 4400
Connection ~ 7550 2000
Wire Wire Line
	7550 2000 8050 2000
Wire Wire Line
	8500 2300 8000 2300
Wire Wire Line
	8000 3800 6700 3800
Wire Wire Line
	8000 2300 8000 3800
Wire Wire Line
	3500 2400 7950 2400
Wire Wire Line
	7950 2400 7950 1700
Wire Wire Line
	7950 1700 8500 1700
Wire Wire Line
	8500 4200 8100 4200
Wire Wire Line
	8100 4200 8100 3350
Wire Wire Line
	8100 3350 6700 3350
Wire Wire Line
	6700 3500 6800 3500
Wire Wire Line
	6800 3500 6800 3950
Wire Wire Line
	6800 3950 6700 3950
Wire Wire Line
	6800 3950 6800 4500
Wire Wire Line
	6800 4500 4950 4500
Wire Wire Line
	4950 4500 4950 2800
Wire Wire Line
	3500 2800 4950 2800
Connection ~ 6800 3950
Wire Wire Line
	5500 2900 5500 3200
Wire Wire Line
	5500 3200 5900 3200
Wire Wire Line
	3500 2900 5500 2900
Wire Wire Line
	5550 2700 5550 3650
Wire Wire Line
	5550 3650 5900 3650
Wire Wire Line
	3500 2700 5550 2700
Wire Wire Line
	3500 2000 5600 2000
Wire Wire Line
	5900 3350 5600 3350
Wire Wire Line
	5600 3350 5600 2000
Connection ~ 5600 2000
Wire Wire Line
	5600 2000 7550 2000
Wire Wire Line
	5900 3800 5650 3800
Wire Wire Line
	5650 3800 5650 1900
Connection ~ 5650 1900
Wire Wire Line
	5650 1900 7500 1900
Wire Wire Line
	5900 3950 5800 3950
Wire Wire Line
	5800 3950 5800 4050
$Comp
L Main-Board-rescue:GND-Main_Board-Main-Board-rescue #PWR02
U 1 1 5CB3ADB4
P 5800 4050
F 0 "#PWR02" H 5800 3800 50  0001 C CNN
F 1 "GND" H 5805 3877 50  0000 C CNN
F 2 "" H 5800 4050 50  0000 C CNN
F 3 "" H 5800 4050 50  0000 C CNN
	1    5800 4050
	1    0    0    -1  
$EndComp
$Comp
L Main-Board-rescue:+3.3V-Main_Board-Main-Board-rescue #PWR07
U 1 1 5CB3DCF3
P 6800 2850
F 0 "#PWR07" H 6800 2700 50  0001 C CNN
F 1 "+3.3V" H 6815 3023 50  0000 C CNN
F 2 "" H 6800 2850 50  0000 C CNN
F 3 "" H 6800 2850 50  0000 C CNN
	1    6800 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3050 6800 3050
Wire Wire Line
	6800 3050 6800 2850
Wire Wire Line
	5900 3500 5700 3500
Wire Wire Line
	5700 3500 5700 3050
Wire Wire Line
	5700 3050 5900 3050
Wire Wire Line
	5700 3500 5700 4350
Wire Wire Line
	5700 4350 1500 4350
Wire Wire Line
	1500 4350 1500 2500
Wire Wire Line
	1500 2500 3000 2500
Connection ~ 5700 3500
Wire Wire Line
	1500 2100 1500 1000
Wire Wire Line
	1500 1000 7050 1000
Wire Wire Line
	7050 1000 7050 3650
Wire Wire Line
	7050 3650 6700 3650
Wire Wire Line
	1500 2100 3000 2100
Wire Wire Line
	6700 3200 7000 3200
Wire Wire Line
	7000 3200 7000 1100
Wire Wire Line
	7000 1100 1550 1100
Wire Wire Line
	1550 1100 1550 2200
Wire Wire Line
	1550 2200 3000 2200
NoConn ~ 3500 2300
NoConn ~ 3500 2500
Wire Wire Line
	3600 3700 3600 2200
Wire Wire Line
	3600 2200 3500 2200
Connection ~ 3600 3700
Wire Wire Line
	3500 2600 4850 2600
Wire Wire Line
	4850 2600 4850 1650
$Comp
L Main-Board-rescue:+3.3V-Main_Board-Main-Board-rescue #PWR0103
U 1 1 5CB23E4A
P 4850 1650
F 0 "#PWR0103" H 4850 1500 50  0001 C CNN
F 1 "+3.3V" H 4865 1823 50  0000 C CNN
F 2 "" H 4850 1650 50  0000 C CNN
F 3 "" H 4850 1650 50  0000 C CNN
	1    4850 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5CB13005
P 7250 4150
F 0 "C4" H 7365 4196 50  0000 L CNN
F 1 "100nF" H 7365 4105 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 7288 4000 50  0001 C CNN
F 3 "~" H 7250 4150 50  0001 C CNN
	1    7250 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 3050 7250 3050
Wire Wire Line
	7250 3050 7250 4000
Connection ~ 6800 3050
$Comp
L Main-Board-rescue:GND-Main_Board-Main-Board-rescue #PWR016
U 1 1 5CB26B05
P 7250 4300
F 0 "#PWR016" H 7250 4050 50  0001 C CNN
F 1 "GND" H 7255 4127 50  0000 C CNN
F 2 "" H 7250 4300 50  0000 C CNN
F 3 "" H 7250 4300 50  0000 C CNN
	1    7250 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C3
U 1 1 5CB305A5
P 1050 3100
F 0 "C3" H 1165 3146 50  0000 L CNN
F 1 "47uF" H 1165 3055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 1050 3100 50  0001 C CNN
F 3 "~" H 1050 3100 50  0001 C CNN
	1    1050 3100
	1    0    0    -1  
$EndComp
$Comp
L Main-Board-rescue:GND-Main_Board-Main-Board-rescue #PWR015
U 1 1 5CB30D6E
P 1050 3250
F 0 "#PWR015" H 1050 3000 50  0001 C CNN
F 1 "GND" H 1055 3077 50  0000 C CNN
F 2 "" H 1050 3250 50  0000 C CNN
F 3 "" H 1050 3250 50  0000 C CNN
	1    1050 3250
	1    0    0    -1  
$EndComp
$Comp
L Main-Board-rescue:+3.3V-Main_Board-Main-Board-rescue #PWR014
U 1 1 5CB31393
P 1050 2950
F 0 "#PWR014" H 1050 2800 50  0001 C CNN
F 1 "+3.3V" H 1065 3123 50  0000 C CNN
F 2 "" H 1050 2950 50  0000 C CNN
F 3 "" H 1050 2950 50  0000 C CNN
	1    1050 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5300 3500 5300
Wire Wire Line
	3500 5300 3500 5100
Wire Wire Line
	4200 5300 4350 5300
Wire Wire Line
	4350 5300 4350 5100
$Comp
L Main-Board-rescue:+5V-Main_Board-Main-Board-rescue #PWR017
U 1 1 5CB47F57
P 4350 5100
F 0 "#PWR017" H 4350 4950 50  0001 C CNN
F 1 "+5V" H 4365 5273 50  0000 C CNN
F 2 "" H 4350 5100 50  0000 C CNN
F 3 "" H 4350 5100 50  0000 C CNN
	1    4350 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 3700 3000 3700
Wire Wire Line
	1800 3600 3000 3600
Wire Wire Line
	1650 3100 3000 3100
Wire Wire Line
	1650 3100 1650 4450
Wire Wire Line
	4750 3600 4750 4300
Wire Wire Line
	4750 4300 3000 4300
Wire Wire Line
	3000 4300 3000 5600
Wire Wire Line
	3000 5600 3700 5600
Wire Wire Line
	3500 3600 4750 3600
Wire Wire Line
	3700 5500 1850 5500
Wire Wire Line
	1850 3700 1850 5500
Wire Wire Line
	3700 5400 1800 5400
Wire Wire Line
	1800 3600 1800 5400
$Comp
L Connector_Generic:Conn_02x13_Odd_Even J1
U 1 1 5CB4697E
P 3900 5900
F 0 "J1" H 3950 6717 50  0000 C CNN
F 1 "Conn_02x13_Odd_Even" H 3950 6626 50  0000 C CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_2x13_P2.00mm_Vertical" H 3900 5900 50  0001 C CNN
F 3 "~" H 3900 5900 50  0001 C CNN
	1    3900 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3300 1950 3300
Wire Wire Line
	1950 3500 3000 3500
Wire Wire Line
	3500 3300 4650 3300
Wire Wire Line
	3500 3400 4650 3400
Wire Wire Line
	3500 3500 4650 3500
Wire Wire Line
	4200 5500 4900 5500
Wire Wire Line
	4900 5500 4900 3100
Wire Wire Line
	3500 3100 4900 3100
Wire Wire Line
	1650 4450 4850 4450
Wire Wire Line
	4850 4450 4850 5400
Wire Wire Line
	4850 5400 4200 5400
$EndSCHEMATC

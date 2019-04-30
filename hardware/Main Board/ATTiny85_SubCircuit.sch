EESchema Schematic File Version 4
LIBS:Main Board-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U?
U 1 1 5CBC2B36
P 3300 3300
AR Path="/5CBC2B36" Ref="U?"  Part="1" 
AR Path="/5CBB2EC7/5CBC2B36" Ref="U2"  Part="1" 
F 0 "U2" H 2900 2600 50  0000 R CNN
F 1 "ATtiny85-20PU" H 4100 2600 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 3300 3300 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 3300 3300 50  0001 C CNN
	1    3300 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CBC2B5E
P 3300 3900
AR Path="/5CBC2B5E" Ref="#PWR?"  Part="1" 
AR Path="/5CBB2EC7/5CBC2B5E" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 3300 3650 50  0001 C CNN
F 1 "GND" H 3305 3727 50  0000 C CNN
F 2 "" H 3300 3900 50  0001 C CNN
F 3 "" H 3300 3900 50  0001 C CNN
	1    3300 3900
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x07_Male J?
U 1 1 5CBC2B64
P 6500 5100
AR Path="/5CBC2B64" Ref="J?"  Part="1" 
AR Path="/5CBB2EC7/5CBC2B64" Ref="J3"  Part="1" 
F 0 "J3" H 6608 5581 50  0000 C CNN
F 1 "ATTiny85 Debug" H 6608 5490 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x07_P1.27mm_Vertical" H 6500 5100 50  0001 C CNN
F 3 "~" H 6500 5100 50  0001 C CNN
	1    6500 5100
	-1   0    0    1   
$EndComp
Text HLabel 6300 2700 2    50   Input ~ 0
I2C_SPI_CLOCK
Text HLabel 6300 3100 2    50   Output ~ 0
MISO
Text HLabel 6300 2600 2    50   BiDi ~ 0
SDA_MOSI
Text HLabel 6300 3500 2    50   Input ~ 0
~RESET
Wire Wire Line
	3900 3500 5800 3500
Wire Wire Line
	5750 3400 3900 3400
Wire Wire Line
	3900 3300 5700 3300
Wire Wire Line
	6300 5100 5650 5100
Wire Wire Line
	5650 5100 5650 3800
Wire Wire Line
	5650 3000 4800 3000
Wire Wire Line
	6300 5200 5600 5200
Wire Wire Line
	5600 5200 5600 3900
Wire Wire Line
	6300 5300 5550 5300
Wire Wire Line
	5550 5300 5550 4000
Wire Wire Line
	6300 5400 5800 5400
Wire Wire Line
	5800 5400 5800 5800
$Comp
L power:GND #PWR08
U 1 1 5CC0F8C7
P 5800 5800
F 0 "#PWR08" H 5800 5550 50  0001 C CNN
F 1 "GND" H 5805 5627 50  0000 C CNN
F 2 "" H 5800 5800 50  0001 C CNN
F 3 "" H 5800 5800 50  0001 C CNN
	1    5800 5800
	1    0    0    -1  
$EndComp
Text GLabel 7300 3800 2    50   Input ~ 0
85_PB0
Text GLabel 7300 3900 2    50   Input ~ 0
85_PB1
Text GLabel 7300 4000 2    50   Input ~ 0
85_PB2
Text GLabel 7300 4100 2    50   Input ~ 0
85_PB3
Text GLabel 7300 4200 2    50   Input ~ 0
85_PB4
Text GLabel 7300 4300 2    50   Input ~ 0
85_PB5
Wire Wire Line
	5650 3800 7300 3800
Connection ~ 5650 3800
Wire Wire Line
	5650 3800 5650 3000
Wire Wire Line
	7300 3900 5600 3900
Connection ~ 5600 3900
Wire Wire Line
	5600 3900 5600 3100
Wire Wire Line
	7300 4000 5550 4000
Connection ~ 5550 4000
Wire Wire Line
	5550 4000 5550 3200
Wire Wire Line
	5750 3400 5750 4200
Wire Wire Line
	7300 4200 5750 4200
Connection ~ 5750 4200
Wire Wire Line
	5800 3500 5800 4300
Wire Wire Line
	5700 3300 5700 4100
Wire Wire Line
	7300 4100 5700 4100
Connection ~ 5700 4100
Wire Wire Line
	5700 4100 5700 4900
Wire Wire Line
	7300 4300 5800 4300
Connection ~ 5800 4300
Wire Wire Line
	5800 3500 6200 3500
Connection ~ 5800 3500
$Comp
L power:+3.3V #PWR011
U 1 1 5CBC7A71
P 3300 2700
F 0 "#PWR011" H 3300 2550 50  0001 C CNN
F 1 "+3.3V" H 3315 2873 50  0000 C CNN
F 2 "" H 3300 2700 50  0001 C CNN
F 3 "" H 3300 2700 50  0001 C CNN
	1    3300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4200 5750 4800
Wire Wire Line
	6300 4900 5700 4900
Wire Wire Line
	3900 3200 4850 3200
Wire Wire Line
	3900 3100 5600 3100
Wire Wire Line
	5600 3100 6300 3100
$Comp
L Switch:SW_DIP_x02 SW1
U 1 1 5CB256C6
P 5500 2700
F 0 "SW1" H 5500 3067 50  0000 C CNN
F 1 "SW_DIP_x02" H 5500 2976 50  0000 C CNN
F 2 "Button_Switch_THT:SW_DIP_SPSTx02_Slide_9.78x7.26mm_W7.62mm_P2.54mm" H 5500 2700 50  0001 C CNN
F 3 "~" H 5500 2700 50  0001 C CNN
	1    5500 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2600 6300 2600
Wire Wire Line
	5800 2700 6300 2700
Wire Wire Line
	4800 2600 4800 3000
Connection ~ 4800 3000
Wire Wire Line
	4800 3000 3900 3000
Wire Wire Line
	4850 2700 4850 3200
Connection ~ 4850 3200
Wire Wire Line
	4850 3200 5550 3200
Connection ~ 5600 3100
Wire Wire Line
	4800 2600 5200 2600
Wire Wire Line
	4850 2700 5200 2700
Wire Wire Line
	5800 5000 6300 5000
Wire Wire Line
	5800 4300 5800 5000
Wire Wire Line
	6300 4800 5750 4800
$Comp
L Device:R R2
U 1 1 5CB3212B
P 8500 2650
F 0 "R2" H 8570 2696 50  0000 L CNN
F 1 "10K" H 8570 2605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 8430 2650 50  0001 C CNN
F 3 "~" H 8500 2650 50  0001 C CNN
	1    8500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3500 6200 3350
Wire Wire Line
	6200 3350 8500 3350
Wire Wire Line
	8500 3350 8500 2800
Connection ~ 6200 3500
Wire Wire Line
	6200 3500 6300 3500
$Comp
L Main-Board-rescue:+3.3V-Main_Board-Main-Board-rescue #PWR013
U 1 1 5CB33869
P 8500 2500
F 0 "#PWR013" H 8500 2350 50  0001 C CNN
F 1 "+3.3V" H 8515 2673 50  0000 C CNN
F 2 "" H 8500 2500 50  0000 C CNN
F 3 "" H 8500 2500 50  0000 C CNN
	1    8500 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5CB3B737
P 2000 3150
F 0 "C2" H 2115 3196 50  0000 L CNN
F 1 "100nF" H 2115 3105 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 2038 3000 50  0001 C CNN
F 3 "~" H 2000 3150 50  0001 C CNN
	1    2000 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3000 2000 2700
Wire Wire Line
	2000 2700 3300 2700
Connection ~ 3300 2700
Wire Wire Line
	2000 3300 2000 3900
Wire Wire Line
	2000 3900 3300 3900
Connection ~ 3300 3900
$EndSCHEMATC

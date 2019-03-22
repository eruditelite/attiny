EESchema Schematic File Version 4
LIBS:Blink-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Connector_Generic:Conn_02x10_Odd_Even J1
U 1 1 5CD86BAC
P 2550 3000
F 0 "J1" H 2600 2350 50  0000 C CNN
F 1 "Daughter Board Connector" H 2100 2100 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 2550 3000 50  0001 C CNN
F 3 "~" H 2550 3000 50  0001 C CNN
	1    2550 3000
	1    0    0    -1  
$EndComp
Text Label 1650 2600 0    50   ~ 0
ATtiny84_PA6
Wire Wire Line
	1650 2600 2350 2600
Text Label 1650 2700 0    50   ~ 0
ATtiny84_PA7
Wire Wire Line
	1650 2700 2350 2700
Text Label 1650 2800 0    50   ~ 0
ATtiny84_PB2
Text Label 1650 2900 0    50   ~ 0
ATtiny84_PA5
Text Label 1650 3000 0    50   ~ 0
ATtiny84_PA4
Text Label 1650 3100 0    50   ~ 0
ATtiny84_PA3
Text Label 1650 3200 0    50   ~ 0
ATtiny84_PA2
Text Label 1650 3300 0    50   ~ 0
ATtiny84_PA1
Text Label 1650 3400 0    50   ~ 0
ATtiny84_PA0
Wire Wire Line
	1650 2800 2350 2800
Wire Wire Line
	1650 2900 2350 2900
Wire Wire Line
	1650 3000 2350 3000
Wire Wire Line
	1650 3100 2350 3100
Wire Wire Line
	1650 3200 2350 3200
Wire Wire Line
	1650 3300 2350 3300
Wire Wire Line
	1650 3400 2350 3400
Wire Wire Line
	2350 3500 2300 3500
Wire Wire Line
	2300 3500 2300 2450
$Comp
L power:+5V #PWR0101
U 1 1 5CD8E5C1
P 2300 2450
F 0 "#PWR0101" H 2300 2300 50  0001 C CNN
F 1 "+5V" H 2315 2623 50  0000 C CNN
F 2 "" H 2300 2450 50  0001 C CNN
F 3 "" H 2300 2450 50  0001 C CNN
	1    2300 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2600 2950 2600
Wire Wire Line
	2950 2600 2950 2700
Wire Wire Line
	2850 2700 2950 2700
Connection ~ 2950 2700
Wire Wire Line
	2950 2700 2950 3750
$Comp
L power:GND #PWR0102
U 1 1 5CD8E7FF
P 2950 3750
F 0 "#PWR0102" H 2950 3500 50  0001 C CNN
F 1 "GND" H 2955 3577 50  0000 C CNN
F 2 "" H 2950 3750 50  0001 C CNN
F 3 "" H 2950 3750 50  0001 C CNN
	1    2950 3750
	1    0    0    -1  
$EndComp
Text Label 3600 2800 2    50   ~ 0
ATtiny84_PB1
Wire Wire Line
	2850 3500 3050 3500
Wire Wire Line
	3050 3500 3050 2450
$Comp
L power:+3.3V #PWR0103
U 1 1 5CD8E9EA
P 3050 2450
F 0 "#PWR0103" H 3050 2300 50  0001 C CNN
F 1 "+3.3V" H 3065 2623 50  0000 C CNN
F 2 "" H 3050 2450 50  0001 C CNN
F 3 "" H 3050 2450 50  0001 C CNN
	1    3050 2450
	1    0    0    -1  
$EndComp
Text Label 3600 2900 2    50   ~ 0
ATtiny84_PB0
Text Label 3600 3000 2    50   ~ 0
ATtiny85_PB0
Text Label 3600 3100 2    50   ~ 0
ATtiny85_PB1
Text Label 3600 3200 2    50   ~ 0
ATtiny85_PB2
Text Label 3600 3300 2    50   ~ 0
ATtiny85_PB4
Text Label 3600 3400 2    50   ~ 0
ATtiny85_PB3
Wire Wire Line
	2850 2800 3600 2800
Wire Wire Line
	2850 2900 3600 2900
Wire Wire Line
	2850 3000 3600 3000
Wire Wire Line
	2850 3100 3600 3100
Wire Wire Line
	2850 3200 3600 3200
Wire Wire Line
	2850 3300 3600 3300
Wire Wire Line
	2850 3400 3600 3400
$EndSCHEMATC

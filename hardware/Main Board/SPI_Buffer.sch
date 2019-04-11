EESchema Schematic File Version 4
LIBS:Main Board-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
L Transistor_BJT:2N3906 Q?
U 1 1 5CB3AD2E
P 4000 2100
AR Path="/5CB3AD2E" Ref="Q?"  Part="1" 
AR Path="/5CBB2EC7/5CB3AD2E" Ref="Q?"  Part="1" 
AR Path="/5CB07E0B/5CB3AD2E" Ref="Q?"  Part="1" 
F 0 "Q?" H 4190 2054 50  0000 L CNN
F 1 "2N3906" H 4190 2145 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4200 2025 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3906.pdf" H 4000 2100 50  0001 L CNN
	1    4000 2100
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5CB3AD34
P 3550 2100
AR Path="/5CB3AD34" Ref="R?"  Part="1" 
AR Path="/5CBB2EC7/5CB3AD34" Ref="R?"  Part="1" 
AR Path="/5CB07E0B/5CB3AD34" Ref="R?"  Part="1" 
F 0 "R?" V 3343 2100 50  0000 C CNN
F 1 "47" V 3434 2100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3480 2100 50  0001 C CNN
F 3 "~" H 3550 2100 50  0001 C CNN
	1    3550 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5CB3AD3A
P 3800 1850
AR Path="/5CB3AD3A" Ref="R?"  Part="1" 
AR Path="/5CBB2EC7/5CB3AD3A" Ref="R?"  Part="1" 
AR Path="/5CB07E0B/5CB3AD3A" Ref="R?"  Part="1" 
F 0 "R?" H 3730 1804 50  0000 R CNN
F 1 "47K" H 3730 1895 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3730 1850 50  0001 C CNN
F 3 "~" H 3800 1850 50  0001 C CNN
	1    3800 1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 2100 3800 2100
Wire Wire Line
	3800 2000 3800 2100
Connection ~ 3800 2100
$Comp
L Amplifier_Operational:LM358 U?
U 3 1 5CB3AD43
P 4000 2600
AR Path="/5CBB2EC7/5CB3AD43" Ref="U?"  Part="3" 
AR Path="/5CB07E0B/5CB3AD43" Ref="U?"  Part="3" 
F 0 "U?" H 3958 2646 50  0000 L CNN
F 1 "LM358" H 3958 2555 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_Socket" H 4000 2600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 4000 2600 50  0001 C CNN
	3    4000 2600
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CB3AD49
P 4100 2900
AR Path="/5CBB2EC7/5CB3AD49" Ref="#PWR?"  Part="1" 
AR Path="/5CB07E0B/5CB3AD49" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4100 2650 50  0001 C CNN
F 1 "GND" H 4105 2727 50  0000 C CNN
F 2 "" H 4100 2900 50  0001 C CNN
F 3 "" H 4100 2900 50  0001 C CNN
	1    4100 2900
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5CB3AD4F
P 3550 1400
F 0 "#PWR?" H 3550 1250 50  0001 C CNN
F 1 "+5V" H 3565 1573 50  0000 C CNN
F 2 "" H 3550 1400 50  0001 C CNN
F 3 "" H 3550 1400 50  0001 C CNN
	1    3550 1400
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 5CB3AD55
P 3000 2000
F 0 "Q?" V 3235 2000 50  0000 C CNN
F 1 "2N3904" V 3326 2000 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 3200 1925 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 3000 2000 50  0001 L CNN
	1    3000 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5CB3AD5B
P 3300 1750
F 0 "R?" H 3370 1796 50  0000 L CNN
F 1 "R" H 3370 1705 50  0000 L CNN
F 2 "" V 3230 1750 50  0001 C CNN
F 3 "~" H 3300 1750 50  0001 C CNN
	1    3300 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1800 3000 1500
Wire Wire Line
	3000 1500 3300 1500
Wire Wire Line
	4100 1500 4100 1900
Wire Wire Line
	3800 1700 3800 1500
Connection ~ 3800 1500
Wire Wire Line
	3800 1500 4100 1500
Wire Wire Line
	3300 1600 3300 1500
Connection ~ 3300 1500
Wire Wire Line
	3300 1500 3550 1500
Wire Wire Line
	3200 2100 3300 2100
Wire Wire Line
	3300 2100 3300 1900
Connection ~ 3300 2100
Wire Wire Line
	3300 2100 3400 2100
Wire Wire Line
	3550 1500 3550 1400
Connection ~ 3550 1500
Wire Wire Line
	3550 1500 3800 1500
$Comp
L Transistor_BJT:2N3906 Q?
U 1 1 5CB44E66
P 4000 5600
AR Path="/5CB44E66" Ref="Q?"  Part="1" 
AR Path="/5CBB2EC7/5CB44E66" Ref="Q?"  Part="1" 
AR Path="/5CB07E0B/5CB44E66" Ref="Q?"  Part="1" 
F 0 "Q?" H 4190 5554 50  0000 L CNN
F 1 "2N3906" H 4190 5645 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4200 5525 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3906.pdf" H 4000 5600 50  0001 L CNN
	1    4000 5600
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5CB44E6C
P 3550 5600
AR Path="/5CB44E6C" Ref="R?"  Part="1" 
AR Path="/5CBB2EC7/5CB44E6C" Ref="R?"  Part="1" 
AR Path="/5CB07E0B/5CB44E6C" Ref="R?"  Part="1" 
F 0 "R?" V 3343 5600 50  0000 C CNN
F 1 "47" V 3434 5600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3480 5600 50  0001 C CNN
F 3 "~" H 3550 5600 50  0001 C CNN
	1    3550 5600
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5CB44E72
P 3800 5350
AR Path="/5CB44E72" Ref="R?"  Part="1" 
AR Path="/5CBB2EC7/5CB44E72" Ref="R?"  Part="1" 
AR Path="/5CB07E0B/5CB44E72" Ref="R?"  Part="1" 
F 0 "R?" H 3730 5304 50  0000 R CNN
F 1 "47K" H 3730 5395 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3730 5350 50  0001 C CNN
F 3 "~" H 3800 5350 50  0001 C CNN
	1    3800 5350
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 5600 3800 5600
Wire Wire Line
	3800 5500 3800 5600
Connection ~ 3800 5600
$Comp
L Amplifier_Operational:LM358 U?
U 3 1 5CB44E7B
P 4000 6100
AR Path="/5CBB2EC7/5CB44E7B" Ref="U?"  Part="3" 
AR Path="/5CB07E0B/5CB44E7B" Ref="U?"  Part="3" 
F 0 "U?" H 3958 6146 50  0000 L CNN
F 1 "LM358" H 3958 6055 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_Socket" H 4000 6100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 4000 6100 50  0001 C CNN
	3    4000 6100
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CB44E81
P 4100 6400
AR Path="/5CBB2EC7/5CB44E81" Ref="#PWR?"  Part="1" 
AR Path="/5CB07E0B/5CB44E81" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4100 6150 50  0001 C CNN
F 1 "GND" H 4105 6227 50  0000 C CNN
F 2 "" H 4100 6400 50  0001 C CNN
F 3 "" H 4100 6400 50  0001 C CNN
	1    4100 6400
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5CB44E87
P 3550 4900
F 0 "#PWR?" H 3550 4750 50  0001 C CNN
F 1 "+5V" H 3565 5073 50  0000 C CNN
F 2 "" H 3550 4900 50  0001 C CNN
F 3 "" H 3550 4900 50  0001 C CNN
	1    3550 4900
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 5CB44E8D
P 3000 5500
F 0 "Q?" V 3235 5500 50  0000 C CNN
F 1 "2N3904" V 3326 5500 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 3200 5425 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 3000 5500 50  0001 L CNN
	1    3000 5500
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5CB44E93
P 3300 5250
F 0 "R?" H 3370 5296 50  0000 L CNN
F 1 "R" H 3370 5205 50  0000 L CNN
F 2 "" V 3230 5250 50  0001 C CNN
F 3 "~" H 3300 5250 50  0001 C CNN
	1    3300 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 5300 3000 5000
Wire Wire Line
	3000 5000 3300 5000
Wire Wire Line
	4100 5000 4100 5400
Wire Wire Line
	3800 5200 3800 5000
Connection ~ 3800 5000
Wire Wire Line
	3800 5000 4100 5000
Wire Wire Line
	3300 5100 3300 5000
Connection ~ 3300 5000
Wire Wire Line
	3300 5000 3550 5000
Wire Wire Line
	3200 5600 3300 5600
Wire Wire Line
	3300 5600 3300 5400
Connection ~ 3300 5600
Wire Wire Line
	3300 5600 3400 5600
Wire Wire Line
	3550 5000 3550 4900
Connection ~ 3550 5000
Wire Wire Line
	3550 5000 3800 5000
Text HLabel 6500 3000 0    50   Input ~ 0
MOSI
Text HLabel 9750 3850 0    50   Input ~ 0
MISO
Text HLabel 2300 2100 0    50   Input ~ 0
~ENABLE_A
Text HLabel 2300 5600 0    50   Input ~ 0
~ENABLE_B
Wire Wire Line
	2300 2100 2800 2100
Wire Wire Line
	2300 5600 2800 5600
$Comp
L Amplifier_Operational:LM358 U?
U 2 1 5CB6737E
P 7350 2400
F 0 "U?" H 7350 2033 50  0000 C CNN
F 1 "LM358" H 7350 2124 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_Socket" H 7350 2400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 7350 2400 50  0001 C CNN
	2    7350 2400
	1    0    0    1   
$EndComp
Wire Wire Line
	7050 2300 6950 2300
Wire Wire Line
	6950 2300 6950 2150
Wire Wire Line
	6950 2150 7750 2150
Wire Wire Line
	7750 2400 7650 2400
Wire Wire Line
	7750 2400 7750 2150
$Comp
L Amplifier_Operational:LM358 U?
U 1 1 5CB6738D
P 7000 3900
F 0 "U?" H 7000 4267 50  0000 C CNN
F 1 "LM358" H 7000 4176 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_Socket" H 7000 3900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 7000 3900 50  0001 C CNN
	1    7000 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7400 4150 6600 4150
Wire Wire Line
	7400 4000 7400 4150
Wire Wire Line
	7300 4000 7400 4000
Wire Wire Line
	6600 4150 6600 3900
Wire Wire Line
	6600 3900 6700 3900
$EndSCHEMATC

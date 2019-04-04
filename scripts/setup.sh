#!/bin/sh

gpio -g mode 0 alt0
gpio -g mode 1 alt0
gpio -g mode 9 in
gpio -g mode 10 in
gpio -g mode 11 in

gpio -g mode 2 alt0
gpio -g mode 3 alt0
gpio -g mode 9 in
gpio -g mode 10 in
gpio -g mode 11 in

gpio -g mode 22 out
gpio -g mode 23 out
gpio -g write 23 0
gpio -g write 22 1
gpio -g write 22 0
gpio -g write 22 1

gpio -g mode 24 out
gpio -g mode 27 out
gpio -g write 24 0
gpio -g write 27 1
gpio -g write 27 0
gpio -g write 27 1

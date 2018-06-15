#!/bin/sh

AVRTARGET=84 make -C examples84/blink $@
AVRTARGET=85 make -C examples85/blink $@
AVRTARGET=84 make -C examples84/square $@
AVRTARGET=85 make -C examples85/square $@
AVRTARGET=85 make -C examples85/wave $@
AVRTARGET=85 make -C examples85/adc $@
AVRTARGET=85 make -C examples85/activity $@

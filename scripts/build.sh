#!/bin/sh

AVRTARGET=84 make $@
AVRTARGET=84 make -C examples84/blink $@
AVRTARGET=85 make -C examples85/blink $@
AVRTARGET=84 make -C examples84/square $@
AVRTARGET=85 make -C examples85/square $@

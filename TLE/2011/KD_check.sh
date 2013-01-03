#!/usr/bin/zsh

gcc -O2 $1.c
time ./a.out < KD_heavy.in > /dev/null

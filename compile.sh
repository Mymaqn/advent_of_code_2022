#!/bin/bash
gcc -Wall -O3 main.c syscall.S my_lib.c my_lib.h -nostdlib -static -s -o main
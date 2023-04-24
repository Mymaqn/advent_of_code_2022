#!/bin/bash
if [ "$1" == "final" ]; then
    gcc -Wall -O3 main.c syscall.S my_lib.c my_lib.h -nostdlib -static -s -o main
else
    gcc -Wall main.c syscall.S my_lib.c my_lib.h -nostdlib -static -g -o main
fi
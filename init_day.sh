#!/bin/bash
if [ -z "$1" ]
then
    echo "Specify day in arg1"
    exit
fi

mkdir $1
cp main.c my_lib.c my_lib.h syscall.S update_my_lib.sh compile.sh $1/
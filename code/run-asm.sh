#!/bin/bash
echo complier
./a.out
echo cat code.asm
cat code.asm
echo asm
nasm -f elf code.asm -o test.o ; gcc -m32 test.o -o test1
echo run
./test1

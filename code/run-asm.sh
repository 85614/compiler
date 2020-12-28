#!/bin/bash
echo complie
./a.out
echo cat code.asm
cat code.asm
echo nasm -f elf code.asm -o test.o 
nasm -f elf code.asm -o test.o 
echo  gcc -m32 test.o -o test1
gcc -m32 test.o -o test1
echo ./test1
./test1

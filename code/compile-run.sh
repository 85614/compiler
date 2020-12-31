#!/bin/bash
echo ./build/compiler
./build/compiler
echo

echo cat ./output/asm.output
cat ./output/asm.output
echo

echo nasm -f elf ./output/asm.output -o ./build/test.o 
nasm -f elf ./output/asm.output -o ./build/test.o 
echo

echo  gcc -m32 ./build/test.o -o ./build/test
gcc -m32 ./build/test.o -o ./build/test
echo

echo ./build/test
./build/test
echo
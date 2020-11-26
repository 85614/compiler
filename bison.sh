#! /bin/bash
echo "flex"
flex  c99.l
echo "bison"
bison -d c99.y 
echo "gcc"
gcc lex.yy.c c99.tab.c base.c -ll
echo "run"
./a.out in.txt out.txt
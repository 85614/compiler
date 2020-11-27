echo "flex"
flex  c99.l
echo "gcc"
gcc lex_main.c lex.yy.c base.c -ll
echo "run"
./a.out in.txt out.txt
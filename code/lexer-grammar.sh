#!/bin/bash
echo ./build/compiler
./build/compiler
echo

echo cat ./output/lexer.output
cat ./output/lexer.output
echo

echo cat ./output/grammar.output
cat ./output/grammar.output
echo



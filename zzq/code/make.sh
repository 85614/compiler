#!/bin/bash
echo flex
flex lexer.l
echo bison
bison -d  grammar.y
echo gcc
g++ init.cpp tree/TypeNode.cpp grammar.cpp tree/StmtNode.cpp grammar.tab.c lex.yy.c lexer.cpp

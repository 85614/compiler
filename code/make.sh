#!/bin/bash
echo bison
bison -d  grammar.y
echo flex
flex lexer.l
echo gcc
g++ \
  init.cpp \
  symbol/SymbolTable.cpp \
  symbol/Identifier.cpp \
  tree/TypeNode.cpp \
  grammar.cpp \
  tree/StmtNode.cpp \
  grammar.tab.c \
  lex.yy.c \
  lexer.cpp \
  tree/ExprNode.cpp\
  register/register.cpp\
  register/TempValue.cpp\
  base.cpp

echo ./a.out
./a.out
echo cat ./code.asm
cat ./code.asm

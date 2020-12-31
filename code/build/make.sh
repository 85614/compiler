#!/bin/bash
echo bison
bison -d  ../grammar.y
echo

echo flex
flex ../lexer.l
echo

echo gcc
g++ -o compiler\
  ../init.cpp \
  ../symbol/SymbolTable.cpp \
  ../symbol/Identifier.cpp \
  ../tree/TypeNode.cpp \
  ../main.cpp \
  ../tree/StmtNode.cpp \
  ./grammar.tab.c \
  ./lex.yy.c \
  ../lexer.cpp \
  ../tree/ExprNode.cpp\
  ../register/register.cpp\
  ../register/TempValue.cpp\
  ../base.cpp
echo

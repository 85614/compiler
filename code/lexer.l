%x COMMENT
%{
#include "../include.h"
#include "./grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void add_word(const char *token,const char *word_type ,const char *addr_value);


extern char *yytext;
extern int column;
extern FILE * yyin;
extern YYSTYPE yylval;
int token_count = 0;
void yyerror(const char *str);
#define MY_RETURN(x) { yylval.lexeme.tokenCount = ++token_count; add_word(yytext, #x, yytext);  return (x); }
%}
%option yylineno
D   [0-9]
L   [a-zA-Z_]
E   [Ee][+-]?{D}+
delim [ \t\n]
ws    {delim}+

%%
"/*"           { BEGIN(COMMENT) ; }
<COMMENT>"*/"  { BEGIN(INITIAL); }
<COMMENT>{ws}   {printf("inside commenet ws\n");}
<COMMENT>([^*]|\en)+|.
<COMMENT><<EOF>>    {printf("Unterminated comment\n"); return 0;}
 /* C++ comment, a common extension */
"//"[^\n]*
"int"                             { yylval.lexeme.str=strdup(yytext); MY_RETURN(TYPE1); }
"void"                            { yylval.lexeme.str=strdup(yytext); MY_RETURN(TYPE1);}
"main"                            { yylval.lexeme.str=strdup(yytext); MY_RETURN(ID);}
"return"                          { MY_RETURN(RETURN); }
"for"                             { MY_RETURN(FOR);}
"while"                           { MY_RETURN(WHILE);}
"if"                              { MY_RETURN(IF); }
"else"                            { MY_RETURN(ELSE);}
"struct"                          { MY_RETURN(STRUCT);}
";"                               { MY_RETURN(SEMI); }
","                               { MY_RETURN(COMMA); }
"="                               { MY_RETURN(ASSIGNOP); }
(>=)|(<=)|(==)|(!=)|<|>           { yylval.lexeme.str=strdup(yytext); MY_RETURN(RELOP); }
"+"                               { MY_RETURN(PLUS); }
"-"                               { MY_RETURN(MINUS); }
"*"                               { MY_RETURN(STAR); }
"/"                               { MY_RETURN(DIV); }
"%"                               { MY_RETURN(MOD);}
"^"                               { MY_RETURN(POWER);}
"&&"                              { MY_RETURN(AND); }
"&"                               { MY_RETURN(SINGALAND); }
"||"                              { MY_RETURN(OR); }
"!"                               { MY_RETURN(NOT); }
"("                               { MY_RETURN(LP); }
")"                               { MY_RETURN(RP); }
"["                               { MY_RETURN(LB); }
"]"                               { MY_RETURN(RB); }
"{"                               { MY_RETURN(LC); }
"}"                               { MY_RETURN(RC); }
"."                               { MY_RETURN(GETMEMBER); }
{L}({D}|{L})*                     { yylval.lexeme.str=strdup(yytext); MY_RETURN(ID); }
{D}{L}({D}|{L})*                  { MY_RETURN (ERRID); }
[ \t\v\f\r\n]                     { }
(([1-9]|-){D}*)|0                     { yylval.lexeme.str=strdup(yytext); MY_RETURN(INT1);}
%%
int yywrap()
{return 1;}

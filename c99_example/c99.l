D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P                       ([Pp][+-]?{D}+)
FS			(f|F|l|L)
IS                      ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%{
#include <stdio.h>
#include "base.h"
#include "c99.tab.h"

void count(void);
void comment(void);
int check_type(void);

#define MY_RETURN(x) { add_word(yytext, x, #x);  return (x); }
// #x 可以把x变成字符串
#define MY_RETURN2(x) { add_word(yytext, 0, #x); return (#x[1]); }

%}

%%
"/*"			{ comment(); }
"//"[^\n]*              { /* consume //-comment */ }


"auto"			{ count(); MY_RETURN(AUTO); }
"_Bool"			{ count(); MY_RETURN(BOOL); }
"break"			{ count(); MY_RETURN(BREAK); }
"case"			{ count(); MY_RETURN(CASE); }
"char"			{ count(); MY_RETURN(CHAR); }
"_Complex"		{ count(); MY_RETURN(COMPLEX); }
"const"			{ count(); MY_RETURN(CONST); }
"continue"		{ count(); MY_RETURN(CONTINUE); }
"default"		{ count(); MY_RETURN(DEFAULT); }
"do"			{ count(); MY_RETURN(DO); }
"double"		{ count(); MY_RETURN(DOUBLE); }
"else"			{ count(); MY_RETURN(ELSE); }
"enum"			{ count(); MY_RETURN(ENUM); }
"extern"		{ count(); MY_RETURN(EXTERN); }
"float"			{ count(); MY_RETURN(FLOAT); }
"for"			{ count(); MY_RETURN(FOR); }
"goto"			{ count(); MY_RETURN(GOTO); }
"if"			{ count(); MY_RETURN(IF); }
"_Imaginary"		{ count(); MY_RETURN(IMAGINARY); }
"inline"		{ count(); MY_RETURN(INLINE); }
"int"			{ count(); MY_RETURN(INT); }
"long"			{ count(); MY_RETURN(LONG); }
"register"		{ count(); MY_RETURN(REGISTER); }
"restrict"		{ count(); MY_RETURN(RESTRICT); }
"return"		{ count(); MY_RETURN(RETURN); }
"short"			{ count(); MY_RETURN(SHORT); }
"signed"		{ count(); MY_RETURN(SIGNED); }
"sizeof"		{ count(); MY_RETURN(SIZEOF); }
"static"		{ count(); MY_RETURN(STATIC); }
"struct"		{ count(); MY_RETURN(STRUCT); }
"switch"		{ count(); MY_RETURN(SWITCH); }
"typedef"		{ count(); MY_RETURN(TYPEDEF); }
"union"			{ count(); MY_RETURN(UNION); }
"unsigned"		{ count(); MY_RETURN(UNSIGNED); }
"void"			{ count(); MY_RETURN(VOID); }
"volatile"		{ count(); MY_RETURN(VOLATILE); }
"while"			{ count(); MY_RETURN(WHILE); }

{L}({L}|{D})*		{ count(); /*MY_RETURN(check_type())*/MY_RETURN(IDENTIFIER); }

0[xX]{H}+{IS}?		{ count(); MY_RETURN(CONSTANT); }
0[0-7]*{IS}?		{ count(); MY_RETURN(CONSTANT); }
[1-9]{D}*{IS}?		{ count(); MY_RETURN(CONSTANT); }
L?'(\\.|[^\\'\n])+'	{ count(); MY_RETURN(CONSTANT); }

{D}+{E}{FS}?		{ count(); MY_RETURN(CONSTANT); }
{D}*"."{D}+{E}?{FS}?	{ count(); MY_RETURN(CONSTANT); }
{D}+"."{D}*{E}?{FS}?	{ count(); MY_RETURN(CONSTANT); }
0[xX]{H}+{P}{FS}?	{ count(); MY_RETURN(CONSTANT); }
0[xX]{H}*"."{H}+{P}?{FS}?     { count(); MY_RETURN(CONSTANT); }
0[xX]{H}+"."{H}*{P}?{FS}?     { count(); MY_RETURN(CONSTANT); }


L?\"(\\.|[^\\"\n])*\"	{ count(); MY_RETURN(STRING_LITERAL); }

"..."			{ count(); MY_RETURN(ELLIPSIS); }
">>="			{ count(); MY_RETURN(RIGHT_ASSIGN); }
"<<="			{ count(); MY_RETURN(LEFT_ASSIGN); }
"+="			{ count(); MY_RETURN(ADD_ASSIGN); }
"-="			{ count(); MY_RETURN(SUB_ASSIGN); }
"*="			{ count(); MY_RETURN(MUL_ASSIGN); }
"/="			{ count(); MY_RETURN(DIV_ASSIGN); }
"%="			{ count(); MY_RETURN(MOD_ASSIGN); }
"&="			{ count(); MY_RETURN(AND_ASSIGN); }
"^="			{ count(); MY_RETURN(XOR_ASSIGN); }
"|="			{ count(); MY_RETURN(OR_ASSIGN); }
">>"			{ count(); MY_RETURN(RIGHT_OP); }
"<<"			{ count(); MY_RETURN(LEFT_OP); }
"++"			{ count(); MY_RETURN(INC_OP); }
"--"			{ count(); MY_RETURN(DEC_OP); }
"->"			{ count(); MY_RETURN(PTR_OP); }
"&&"			{ count(); MY_RETURN(AND_OP); }
"||"			{ count(); MY_RETURN(OR_OP); }
"<="			{ count(); MY_RETURN(LE_OP); }
">="			{ count(); MY_RETURN(GE_OP); }
"=="			{ count(); MY_RETURN(EQ_OP); }
"!="			{ count(); MY_RETURN(NE_OP); }
";"			{ count(); MY_RETURN2(';'); }
("{"|"<%")		{ count(); MY_RETURN2('{'); }
("}"|"%>")		{ count(); MY_RETURN2('}'); }
","			{ count(); MY_RETURN2(','); }
":"			{ count(); MY_RETURN2(':'); }
"="			{ count(); MY_RETURN2('='); }
"("			{ count(); MY_RETURN2('('); }
")"			{ count(); MY_RETURN2(')'); }
("["|"<:")		{ count(); MY_RETURN2('['); }
("]"|":>")		{ count(); MY_RETURN2(']'); }
"."			{ count(); MY_RETURN2('.'); }
"&"			{ count(); MY_RETURN2('&'); }
"!"			{ count(); MY_RETURN2('!'); }
"~"			{ count(); MY_RETURN2('~'); }
"-"			{ count(); MY_RETURN2('-'); }
"+"			{ count(); MY_RETURN2('+'); }
"*"			{ count(); MY_RETURN2('*'); }
"/"			{ count(); MY_RETURN2('/'); }
"%"			{ count(); MY_RETURN2('%'); }
"<"			{ count(); MY_RETURN2('<'); }
">"			{ count(); MY_RETURN2('>'); }
"^"			{ count(); MY_RETURN2('^'); }
"|"			{ count(); MY_RETURN2('|'); }
"?"			{ count(); MY_RETURN2('?'); }

[ \t\v\n\f]		{ count(); }
.			{ /* Add code to complain about unmatched characters */ }

%%

int yywrap(void)
{
	return 1;
}
extern int input();

void comment(void)
{
	char c, prev = 0;
    
	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	perror("unterminated comment");
}


int column = 0;

void count(void)
{
	int i;
	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}


int check_type(void)
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return TYPE_NAME;
*
*	return IDENTIFIER;
*/

/*
*	it actually will only return IDENTIFIER
*/

	return IDENTIFIER;
}




const char *get_token_str(int c) {
	switch(c) {
		case IDENTIFIER:
        return "IDENTIFIER";
        break;
    case CONSTANT:
        return "CONSTANT";
        break;
    case STRING_LITERAL:
        return "STRING_LITERAL";
        break;
    case SIZEOF:
        return "SIZEOF";
        break;
    case PTR_OP:
        return "PTR_OP";
        break;
    case INC_OP:
        return "INC_OP";
        break;
    case DEC_OP:
        return "DEC_OP";
        break;
    case LEFT_OP:
        return "LEFT_OP";
        break;
    case RIGHT_OP:
        return "RIGHT_OP";
        break;
    case LE_OP:
        return "LE_OP";
        break;
    case GE_OP:
        return "GE_OP";
        break;
    case EQ_OP:
        return "EQ_OP";
        break;
    case NE_OP:
        return "NE_OP";
        break;
    case AND_OP:
        return "AND_OP";
        break;
    case OR_OP:
        return "OR_OP";
        break;
    case MUL_ASSIGN:
        return "MUL_ASSIGN";
        break;
    case DIV_ASSIGN:
        return "DIV_ASSIGN";
        break;
    case MOD_ASSIGN:
        return "MOD_ASSIGN";
        break;
    case ADD_ASSIGN:
        return "ADD_ASSIGN";
        break;
    case SUB_ASSIGN:
        return "SUB_ASSIGN";
        break;
    case LEFT_ASSIGN:
        return "LEFT_ASSIGN";
        break;
    case RIGHT_ASSIGN:
        return "RIGHT_ASSIGN";
        break;
    case AND_ASSIGN:
        return "AND_ASSIGN";
        break;
    case XOR_ASSIGN:
        return "XOR_ASSIGN";
        break;
    case OR_ASSIGN:
        return "OR_ASSIGN";
        break;
    case TYPE_NAME:
        return "TYPE_NAME";
        break;
    case TYPEDEF:
        return "TYPEDEF";
        break;
    case EXTERN:
        return "EXTERN";
        break;
    case STATIC:
        return "STATIC";
        break;
    case AUTO:
        return "AUTO";
        break;
    case REGISTER:
        return "REGISTER";
        break;
    case INLINE:
        return "INLINE";
        break;
    case RESTRICT:
        return "RESTRICT";
        break;
    case CHAR:
        return "CHAR";
        break;
    case SHORT:
        return "SHORT";
        break;
    case INT:
        return "INT";
        break;
    case LONG:
        return "LONG";
        break;
    case SIGNED:
        return "SIGNED";
        break;
    case UNSIGNED:
        return "UNSIGNED";
        break;
    case FLOAT:
        return "FLOAT";
        break;
    case DOUBLE:
        return "DOUBLE";
        break;
    case CONST:
        return "CONST";
        break;
    case VOLATILE:
        return "VOLATILE";
        break;
    case VOID:
        return "VOID";
        break;
    case BOOL:
        return "BOOL";
        break;
    case COMPLEX:
        return "COMPLEX";
        break;
    case IMAGINARY:
        return "IMAGINARY";
        break;
    case STRUCT:
        return "STRUCT";
        break;
    case UNION:
        return "UNION";
        break;
    case ENUM:
        return "ENUM";
        break;
    case ELLIPSIS:
        return "ELLIPSIS";
        break;
    case CASE:
        return "CASE";
        break;
    case DEFAULT:
        return "DEFAULT";
        break;
    case IF:
        return "IF";
        break;
    case ELSE:
        return "ELSE";
        break;
    case SWITCH:
        return "SWITCH";
        break;
    case WHILE:
        return "WHILE";
        break;
    case DO:
        return "DO";
        break;
    case FOR:
        return "FOR";
        break;
    case GOTO:
        return "GOTO";
        break;
    case CONTINUE:
        return "CONTINUE";
        break;
    case BREAK:
        return "BREAK";
        break;
    case RETURN:
        return "RETURN";
        break;
    default:
        return 0;
	}
}
#include <stdio.h>

int token_count = 0;
extern FILE *yyin, *yyout;
extern int yylex();
extern const char *yytext;
extern const char *get_token_str(int c);

void print_words();
int main (int argc, char ** argv) {
	if (argc>=2){
	  if ((yyin = fopen(argv[1], "r")) == NULL){
	    printf("Can't open file %s\n", argv[1]);
	    return 1;
	  }
	  if (argc>=3){
	    yyout=fopen(argv[2], "w");
	  }
	}
	/* yyin和yyout是lex中定义的输入输出文件指针，它们指明了
	 * lex生成的词法分析器从哪里获得输入和输出到哪里。
	 * 默认：键盘输入，屏幕输出。 
	 */    


	int c = 0;
	// printf("%-18s%-22s%-12s\n", "单词", "词素", "属性");
	while (c = yylex()){
		++ token_count;
        // const char *s = get_token_str(c);
        // if (s)
		//     printf("%-16s%-20s%-10s\n", get_token_str(c), yytext, "no");
        // else 
        //     printf("%-16s%-20s%-10s\n", yytext, yytext, "no");
	
	}
	print_words();
	return 0;
}
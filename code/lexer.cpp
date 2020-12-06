#include <vector>
#include <string.h>
#include <string>
#include "include.h"
#include "grammar.tab.h"
using std::string;
using std::vector;
struct word{
    string token;
    string word_type;
    string addr_value;
    IDNode *idptr = nullptr;
    void printAttr(){
        if (word_type == "INT"){
            cout <<addr_value;
        }
        else if (word_type == "ID"){
            
            cout << idptr->realID;
        }
    }
};
extern YYSTYPE yylval;
vector<word*> word_list;
void add_word(const char *token,const char *word_type ,const char *addr_value) {
    word *new_word = new word();
    new_word->token = token;
    new_word->word_type = word_type;
    if (new_word->word_type == "INT1") {
        new_word->word_type = "INT";
        new_word->addr_value = addr_value;
    } else if (new_word->word_type == "ID") {
        IDNode* id = new IDNode(yylval.lexeme.str);
        id->setTokenCount(yylval.lexeme);
        void *str = (void*)yylval.lexeme.str;
        yylval.id = id;
        new_word->idptr = id;
        // int temp = &addr_value;
        new_word->addr_value = "标识符地址";
        free(str);
    } else {
        new_word->addr_value = "";
    }
    word_list.push_back(new_word);
}

void print_word_list() {
    FILE *f;    
    // if((f = fopen("word.txt", "w")) == NULL)
    //     printf("word.txt open failed. \n");
    f = stdout;
    fprintf(f, "%-18s%-22s%-12s\n", "单词", "词素", "属性");
    for (int i = 0; i < word_list.size(); ++i) {
        word *ptr = word_list[i];
        fprintf(f, "%-16s%-20s", ptr->word_type.c_str(), ptr->token.c_str());
        ptr->printAttr();
        fprintf(f, "\n");
    }
}
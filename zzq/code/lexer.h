#include <vector>
#include <string.h>
#include <string>
using std::string;
using std::vector;
struct word{
    string token;
    string word_type;
    string addr_value;
};

vector<word*> word_list;
void add_word(const char *token,const char *word_type ,const char *addr_value) {
    word *new_word = new word();
    new_word->token = token;
    new_word->word_type = word_type;
    if (new_word->word_type == "INT1") {
        new_word->addr_value = addr_value;
    } else if (new_word->word_type == "ID1") {
        // int temp = &addr_value;
        new_word->addr_value = "标识符地址";
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
        fprintf(f, "%-16s%-20s%-10s", ptr->token.c_str(), ptr->word_type.c_str(), ptr->addr_value.c_str());
        fprintf(f, "\n");
    }
}
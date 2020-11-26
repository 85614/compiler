#include <string.h>
enum type_enum {
    CHAR_T, UNSIGNED_CHAR_T, SHORT_T, UNSIGNED_SHORT_T, 
    INT_T, UNSIGNED_INT_T, LONG_LONG_T, UNSIGNED_LONG_LONG,
    FLOAT_T, DOUBLE_t
};


struct const_t{
    int type;
    union 
    {
        int ival;
    }val;
};

struct type_t{
    
};

struct id_t{
    const char *token;
};

struct stmt_t{

};

struct op_t{

};

struct expr_t{

};

struct symbol_table{
    struct symbol_table *parent;

};



struct const_t* add_const(const char *token, int type);




struct vector{
    void **list;
    int size;
    int capacity;
};
void vector_init(struct vector*v);
void vector_destory(struct vector *v);

void vector_add(struct vector *v, void *ptr);

struct vector id_list;

struct id_t* add_id(const char *token);

struct vector word_list;

struct word{
    const char *token;
    int word_type;
    const char *word_type_str;
    void *pval;
};

char *new_str(const char*s);

void add_word(const char *token, int word_type, const char* word_type_str);

void print_words();





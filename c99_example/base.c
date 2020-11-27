#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "base.h"
#include "c99.tab.h"

struct const_t* add_const(const char *token, int type){
    struct const_t*ptr = malloc(sizeof(struct const_t));
    ptr->type = INT_T;
    ptr->val.ival = atoi(token);
    return ptr;
}


void vector_init(struct vector*v) {
    v = malloc(sizeof(struct vector));
    v->capacity = 0;
    v->size = 0;
    v->list = 0;
}
void vector_destory(struct vector *v){
    free(v->list);
    free(v);
}

void vector_add(struct vector *v, void *ptr){
    if(v->size == v->capacity){
        v->capacity = v->size * 3 / 2 + 1;
        void **old_list = v->list;
        v->list = malloc(sizeof(void*) * v->capacity);
        memcpy(v->list, old_list, v->size * sizeof(*old_list));
        free(old_list);
    }
    v->list[v->size++] = ptr;
    
}

struct vector id_list;

struct id_t* add_id(const char *token){
    struct id_t*ptr = malloc(sizeof(struct id_t));
    ptr->token = token;
    vector_add((struct vector*)&id_list, ptr);
    return ptr;
}

struct vector word_list;


char *new_str(const char*s){
    int len = strlen(s)+1;
    char*buf = (char*)malloc(len);
    memcpy(buf,s,len);
    return buf;
}

void add_word(const char *token, int word_type, const char* word_type_str){
    struct word* ptr =  (struct word*)malloc(sizeof(struct word));
    ptr->word_type = word_type;
    ptr->word_type_str = word_type_str;
    ptr->token = new_str(token);
    if (word_type == IDENTIFIER){
        ptr->pval = yylval.id_v = add_id(token);
        printf("get a id1: %ld %s\n", (long int)(&yylval.id_v->token), yylval.id_v->token);
    }
    else if (word_type == CONSTANT)
        ptr->pval = yylval.const_v = add_const(token, INT_T);
    else 
        ptr->pval = 0;
    
    vector_add((struct vector*)&word_list, ptr);

}

void print_words(){
    FILE *f;    
    // if((f = fopen("word.txt", "w")) == NULL)
    //     printf("word.txt open failed. \n");
    f = stdout;
    fprintf(f, "%-18s%-22s%-12s\n", "单词", "词素", "属性");
    for (int i = 0; i < word_list.size; ++i) {
        struct word *ptr = word_list.list[i];
        fprintf(f, "%-16s%-20s", ptr->word_type_str, ptr->token);
        if (ptr->word_type == IDENTIFIER)
            fprintf(f, "%-10ld", (long int)ptr->pval);
        else if (ptr->word_type == CONSTANT)
            fprintf(f, "%-10d", ((struct const_t *)(ptr->pval))->val.ival);
        fprintf(f, "\n");

    }
}





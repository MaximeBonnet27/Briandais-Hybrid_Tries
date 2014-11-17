#ifndef TOOLS_H_GUARD
#define TOOLS_H_GUARD

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct word_list{
	char * word;
	struct word_list * next;
} word_list;



char first(char * string);
char * end(char * string);
int max(int a, int b);
int max_3(int a, int b, int c);


void add_word_list(char * word, word_list ** list);
void print_word_list(word_list * list);
#endif

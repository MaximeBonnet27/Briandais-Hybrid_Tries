#ifndef HTRIE_H_GUARD
#define HTRIE_H_GUARD

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "tools.h"

#define EMPTY '0'
#define NON_EMPTY '1'
#define D_X 10
#define D_Y 10
typedef struct HTrie{

	char key;
	char val;
	struct HTrie * inf;
	struct HTrie * eq;
	struct HTrie * sup;

} HTrie;


HTrie * add_HTrie(char * word, HTrie * T);


HTrie * del_HTrie(char * word, HTrie * T);

void free_HTrie(HTrie * T);

HTrie * add_file_HTrie(char * file_name, HTrie * T);

int search_HTrie(char * word, HTrie * T);

int count_words_HTrie(HTrie * T);

int count_null_HTrie(HTrie * T);

int height_HTrie(HTrie * T);

double average_level_HTrie(HTrie * T);


int count_prefix_HTrie(char * prefix, HTrie * T);



void make_plot_file_HTrie(HTrie * T);
#endif

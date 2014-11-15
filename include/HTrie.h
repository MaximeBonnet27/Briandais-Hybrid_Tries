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


HTrie * empty_HTrie();

int is_empty(HTrie * T);

HTrie * new_HTrie(char key, char val, HTrie * inf, HTrie * eq, HTrie * sup);

HTrie  * build_HTrie(char * word);

HTrie * add_HTrie(char * word, HTrie * T);

void free_HTrie(HTrie * T);


void make_plot_file_HTrie(HTrie * T);
#endif
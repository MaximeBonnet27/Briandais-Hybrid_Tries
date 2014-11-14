#ifndef BRTREE_H_GUARD
#define BRTREE_H_GUARD

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "tools.h"


#define D_X 10
#define D_Y 10

/*
* La Briandais Trees structure
*/

typedef struct BRTree{

	char key; 
	struct BRTree * child; 
	struct BRTree * next; 
} BRTree;

/***********************************************/


typedef struct word_list{
	char * word;
	struct word_list * next;
} word_list;

/*
 * Briandais Trees Primitives
 */

/*
 * Returns an empty BRTree
 * ('\0', NULL, NULL)
 */

BRTree * empty_BRTree();

/*
 * Checks if T is empty 
 */

int is_empty(BRTree * T);

/*
* Returns a BRTree (key, child, next)
*/
BRTree * new_BRTree(char key, BRTree * child, BRTree * next);

/*
* Returns a BRTree build from word
*/
BRTree * build_BRTree(char * word);

/*
* Adds word to T
* Returns the new BRTree
*/
BRTree * add_BRTree(char * word, BRTree * T);

/*
* Prints T
*/
void print_BRTree(BRTree * T);

/*
* Adds all the words in file_name into T
* Returns the new BRTree
*/
BRTree * add_file_BRTree(char * file_name, BRTree * T);


/*
* Adds all the words from all the files in dir_name into T
* Returns the new BRTree
<<<<<<< HEAD
*/
=======
*
>>>>>>> d725cd012f5fb11892a5f9490c5347943d02d0dc
BRTree * add_directory_BRTree(char * dir_name, BRTree * T);

/*
* Frees the memory used by T
*/

void free_BRTree(BRTree * T);

/*
 * Delete all the words in file from T
 */
BRTree * del_file_BRTree(char * file_name, BRTree * T);

/***********************************************/

/*
 * Complex methods
 */

/*
* Deletes word from T
* Returns the resulting BRTree
*/
BRTree * del_BRTree(char * word, BRTree * T);

/*
* Searchs word in T
* Returns 1 if word is found, 0 otherwise
*/
int search_BRTree(char * word, BRTree * T);

/*
* Counts how many words there are in T
*/

int count_words_BRTree(BRTree * T);

/*
* Counts how many pointers to NULL there are in T
*/
int count_null_BRTree(BRTree * T);

/*
* Returns the number of nodes in T
*/

int count_nodes_BRTree(BRTree * T);

/*
* Returns T's height
*/
int height_BRTree(BRTree * T);

/*
* Returns T's nodes' average level.
*/
double average_level_BRTree(BRTree * T);
word_list * list_words(BRTree * T);
word_list * add_word_to_list(BRTree * T, word_list ** list, char * prefix);

void add_word_list(char * word, word_list ** list);
void print_word_list(word_list * list);


/* 
* Merge the 2 BRTrees into 1
*/
BRTree * merge_BRTree(BRTree * T1, BRTree * T2);

void make_plot_file_BRTree(BRTree * T);

BRTree * del_directory_BRTree(char * dir_name, BRTree * T);
#endif

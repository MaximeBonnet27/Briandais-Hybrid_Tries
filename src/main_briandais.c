#include "tools.h"
#include "BRTree.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){

	BRTree * t1 = empty_BRTree();
	word_list * l;
	t1 = add_BRTree("a", t1);
	t1 = add_BRTree("z", t1);
	t1 = add_BRTree("the", t1);
	t1 = add_BRTree("t", t1);
	t1 = add_BRTree("at", t1);
	
	l = list_words_BRTree(t1);
	print_word_list(l);	
	free_word_list(l);	

	free_BRTree(t1);
	return EXIT_SUCCESS;	

} 


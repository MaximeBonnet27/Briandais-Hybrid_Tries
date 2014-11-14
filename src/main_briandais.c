#include "tools.h"
#include "BRTree.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){

	BRTree * t1 = empty_BRTree();

	t1 = add_BRTree("a", t1);
	t1 = add_BRTree("z", t1);
	t1 = add_BRTree("the", t1);
	t1 = add_BRTree("t", t1);
	t1 = add_BRTree("at", t1);
	

	BRTree * t2 = empty_BRTree();

	t2 = add_BRTree("ba", t2);
	t2 = add_BRTree("za", t2);
	t2 = add_BRTree("thdde", t2);
	t2 = add_BRTree("ate", t2);
	t2 = add_BRTree("atqsdsqd", t2);

	BRTree * t = merge_BRTree(t1, t2);
	printf("T : \n");
	print_BRTree(t);
	printf("\n T1 : \n");
	print_BRTree(t1);
	printf("\n T2 : \n");
	print_BRTree(t2);
	free_BRTree(t);
	free_BRTree(t1);
	free_BRTree(t2);
	return EXIT_SUCCESS;	

} 


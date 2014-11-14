#include "BRTree.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char ** argv){

	
	BRTree * t = empty_BRTree();
	t = add_file_BRTree("test_files/shakespeare/lll.txt", t);
	
//	t = add_BRTree("Salut", t);
//	t = add_BRTree("Salutations", t);
	make_plot_file_BRTree(t);	

	free_BRTree(t);
	return EXIT_SUCCESS;
}

#include "BRTree.h"
#include "HTrie.h"
#include "tools.h"
int main(int argc, char ** argv){

	HTrie * h;
	BRTree * b;

	h = add_file_HTrie("test_files/shakespeare/lll.txt", h);
	b = HTrie_to_BRTree(h);
	printf("nodes : %d\n", count_nodes_HTrie(h));
	printf("nodes : %d\n", count_nodes_BRTree(b));
	free_BRTree(b);
	free_HTrie(h);

	return EXIT_SUCCESS;
}

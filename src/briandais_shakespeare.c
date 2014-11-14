#include "BRTree.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char ** argv){

	struct timespec start, finish;
	double elapsed;


	printf("Beginning to add words\n");
	clock_gettime(CLOCK_MONOTONIC, &start);

	BRTree * t = empty_BRTree();
	t = add_directory_BRTree("test_files/shakespeare", t);


	clock_gettime(CLOCK_MONOTONIC, &finish);

	
	printf("All words added!\n");


	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("Time elapsed : %f seconds \n", elapsed);


	printf("Tree height : %d\n", height_BRTree(t));
	printf("Nodes : %d\n", count_nodes_BRTree(t));
	printf("Null pointers : %d\n", count_nodes_BRTree(t));
	printf("Words : %d\n", count_words_BRTree(t));
	printf("Average Level : %f\n", average_level_BRTree(t));


	clock_gettime(CLOCK_MONOTONIC, &start);
	t = del_file_BRTree("test_files/shakespeare/othello.txt", t);
	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("Time elapsed after delete: %f seconds \n", elapsed);


	printf("Tree height : %d\n", height_BRTree(t));
	printf("Nodes : %d\n", count_nodes_BRTree(t));
	printf("Null pointers : %d\n", count_nodes_BRTree(t));
	printf("Words : %d\n", count_words_BRTree(t));
	printf("Average Level : %f\n", average_level_BRTree(t));



	free_BRTree(t);

	return EXIT_SUCCESS;
}

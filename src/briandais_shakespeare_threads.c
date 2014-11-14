#include "BRTree.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

BRTree * T;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void * thread_func(void * file_name){
	BRTree * temp = empty_BRTree();
	temp = add_file_BRTree((char *) file_name, temp);
	pthread_mutex_lock(&mutex);
	T = merge_BRTree(T, temp);
	pthread_mutex_unlock(&mutex);
	return NULL;	
}


int main(int argc, char ** argv){

	printf("Beginning to add words\n");
	struct timespec start, finish;
	double elapsed;



	char * dir_name = "test_files/shakespeare";
	DIR * dir = opendir(dir_name);
	struct dirent * entry;

	if(dir == NULL){
		fprintf(stderr,"opendir failed\n");
		return 1;
	}

	int nb_file = 0;
	// We suppose there's no more than 256 file in the directory
	pthread_t tid[256];


	clock_gettime(CLOCK_MONOTONIC, &start);

	while((entry = readdir(dir))){
		if(!strcmp(entry->d_name, "."))
			continue;
		if(!strcmp(entry->d_name, ".."))
			continue;

		char * path = (char *) malloc(sizeof(char) * 256);
		strcpy(path, dir_name);
		strcat(path, "/");
		strcat(path, entry->d_name);



		if(pthread_create(&tid[nb_file++], NULL, thread_func, path) == -1){
			perror("pthread_create");
			exit(1);
		}
	}
	closedir(dir);
	int i;
	for(i = 0; i < nb_file; i++){
		if(pthread_join(tid[i], NULL) != 0){
			perror("pthread_join");
			exit(1);
		}
	}	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	printf("All words added!\n");

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Time elapsed : %f sceconds \n", elapsed);

	printf("Tree height : %d\n", height_BRTree(T));
	printf("Nodes : %d\n", count_nodes_BRTree(T));
	printf("Null pointers : %d\n", count_nodes_BRTree(T));
	printf("Words : %d\n", count_words_BRTree(T));
	printf("Average Level : %f\n", average_level_BRTree(T));

	free_BRTree(T);

	return EXIT_SUCCESS;
}

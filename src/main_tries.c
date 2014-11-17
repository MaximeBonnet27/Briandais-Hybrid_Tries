#include "HTrie.h"

int main(int argc, char ** argv){

	HTrie * T = NULL;
	T = add_file_HTrie("test_files/dactylo", NULL);
	T = del_file_HTrie("test_files/dactylo", NULL);
	free_HTrie(T);		

	return EXIT_SUCCESS;
}


#include "HTrie.h"

int main(int argc, char ** argv){


	HTrie * T = empty_HTrie();
	printf("%d\n", is_empty(T));
	free_HTrie(T);
	T = build_HTrie("Salut");
	free_HTrie(T);		

	return EXIT_SUCCESS;
}


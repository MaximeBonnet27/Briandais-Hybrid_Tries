#include "HTrie.h"

int main(int argc, char ** argv){

	HTrie * T = NULL;
	T = add_HTrie("Salut", T);
	make_plot_file_HTrie(T);	
	free_HTrie(T);		

	return EXIT_SUCCESS;
}


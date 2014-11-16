#include "HTrie.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char ** argv){

	HTrie * t = NULL;

	t = add_file_HTrie("test_files/dactylo", NULL);
	
	make_plot_file_HTrie(t);	

	free_HTrie(t);
	return EXIT_SUCCESS;
}

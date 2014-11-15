#include "HTrie.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char ** argv){

	HTrie * t = empty_HTrie();
	
	t = add_HTrie("Salut", t);
	t = add_HTrie("Salutations", t);
	t = add_HTrie("Aie", t);
	t = add_HTrie("Bah", t);
	t = add_HTrie("Babar", t);

	make_plot_file_HTrie(t);	

	free_HTrie(t);
	return EXIT_SUCCESS;
}

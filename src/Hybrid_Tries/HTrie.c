#include "HTrie.h"

HTrie * add_HTrie(char * word, HTrie * T){

	if(T == NULL){
		T = (HTrie *) malloc(sizeof(HTrie));
		T->key = *word;
		T->inf = NULL;
		T->eq = NULL;
		T->sup = NULL;
		T->val = EMPTY;
	}
	if(*word < T->key){
		T->inf = add_HTrie(word, T->inf);
	}
	else if(*word > T->key){
		T->sup = add_HTrie(word, T->sup);
	}
	else{
		if(*word == '\0'){
			T->val = NON_EMPTY;		
		}
		else{
			T->eq = add_HTrie(++word, T->eq);
		}
	}
	return T;
}


void free_HTrie(HTrie * T){
	if(T == NULL)
		return;
	else {
		free_HTrie(T->inf);
		free_HTrie(T->eq);
		free_HTrie(T->sup);
		free(T);
	}
}

void inside_plot_file(HTrie * T, int x, int y);
int width(HTrie * T);
void make_plot_file_HTrie(HTrie * T){

	inside_plot_file(T, 0, 0);

}

int width(HTrie * T){

	if(T == NULL){
		return 0; 
	}
	else {
		int tmp = width(T->inf) + width(T->sup);
		int w_eq = width(T->eq);
		if(w_eq == 1)
			return tmp;
		else
			return 1 + tmp + w_eq;
	}
}

void inside_plot_file(HTrie * T, int x, int y){

	if(T == NULL)
		return;

	int w_inf, w_eq, w_sup;

	w_eq = width(T->eq);
	w_inf = width(T->inf);	
	w_sup = width(T->sup);

	if(w_eq != 0){
		printf("%c %d %d\n",T->key, x, y);
		printf("%c %d %d\n",T->eq->key, x, y + D_Y);
	}
	inside_plot_file(T->eq, x, y + D_Y);
	printf("\n");
	if(w_inf != 0){
		printf("%c %d %d\n",T->key, x, y);
		printf("%c %d %d\n",T->inf->key, x - (w_inf / 2) * D_X, y + D_Y);
	}
	inside_plot_file(T->inf,  x - (w_inf / 2) * D_X, y + D_Y);
	printf("\n");
	if(w_sup != 0){
		printf("%c %d %d\n",T->key, x, y);
		printf("%c %d %d\n",T->sup->key, x + (w_sup / 2) * D_X, y + D_Y);
	}

	inside_plot_file(T->sup,  x + (w_sup / 2) * D_X, y + D_Y);
	printf("\n");
}

HTrie * add_file_HTrie(char * file_name, HTrie * T){
	FILE * file = fopen(file_name, "r");
	if(file == NULL){
		fprintf(stderr,"fopen failed : %s\n", file_name);
		return NULL;
	}
	char * buffer = malloc(sizeof(char) * 128);
	int i;
	for(i = 0; i < 128; i++) buffer[i] = '\0';
	while(fscanf(file,"%s", buffer) != EOF){
		T = add_HTrie(buffer, T);
		for(i = 0; i < 128; i++) buffer[i] = '\0';
	}
	fclose(file);
	fprintf(stderr,"Added %s\n", file_name);
	return T;
}


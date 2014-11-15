#include "HTrie.h"


HTrie * empty_HTrie(){
	HTrie * new = (HTrie *) malloc(sizeof(HTrie));
	new->key = '\0';
	new->val = EMPTY;
	new->inf = NULL;
	new->eq = NULL;
	new->sup = NULL;
	return new;
}

int is_empty(HTrie * T){
	if(T == NULL){
		return TRUE;
	}
	else {
		if(T->val != EMPTY || T->key != '\0' || T->inf != NULL
				|| T->eq != NULL || T->sup != NULL)
			return FALSE;
	}
	return TRUE;

}

HTrie * new_HTrie(char key, char val, HTrie * inf, HTrie * eq, HTrie * sup){

	HTrie * new = (HTrie *) malloc(sizeof(HTrie));
	new->key = key;
	new->val = val;
	new->inf = inf;
	new->eq = eq;
	new->sup = sup;
	return new;

}

HTrie  * build_HTrie(char * word){

	if(strlen(word) == 1){
		return new_HTrie(first(word), NON_EMPTY, NULL, NULL, NULL);
	}
	else{
		return new_HTrie(first(word), EMPTY, NULL, build_HTrie(end(word)), NULL);
	}
}

HTrie * add_HTrie(char * word, HTrie * T){

	if(is_empty(T)){
		return build_HTrie(word);
	}

	if(first(word) < T->key){
		return new_HTrie(T->key, T->val, add_HTrie(word, T->inf),
				T->eq, T->sup);
	}
	else if (first(word) > T->key){
		return new_HTrie(T->key, T->val, T->inf, T->eq, add_HTrie(word, T->sup));
	}
	else{
		return new_HTrie(T->key, T->val, T->inf, add_HTrie(end(word), T->eq), T->sup);
	}
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
		printf("%c %d %d\n",T->inf->key, x - (w_inf / 2 + 1) * D_X, y + D_Y);
	}
	inside_plot_file(T->inf,  x - (w_inf / 2 + 1) * D_X, y + D_Y);
	printf("\n");
	if(w_sup != 0){
		printf("%c %d %d\n",T->key, x, y);
		printf("%c %d %d\n",T->sup->key, x + (w_sup / 2 + 1) * D_X, y + D_Y);
	}
	
	inside_plot_file(T->sup,  x + (w_sup / 2 + 1) * D_X, y + D_Y);
	printf("\n");
}
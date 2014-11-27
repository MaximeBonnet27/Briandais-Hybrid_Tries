#include "HTrie.h"
#include "BRTree.h"


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
		if(strlen(word) == 1){
			T->val = NON_EMPTY;		
		}
		else{
			T->eq = add_HTrie(++word, T->eq);
		}
	}
	return T;
}

HTrie * del_HTrie(char * word, HTrie * T){

	if(T == NULL)
		return NULL;
	else if(strcmp(word,"") == 0){
		if(T->val == NON_EMPTY){
			if(T->eq != NULL){
				T->val = EMPTY;
			}
			else if(T->inf != NULL){
				T->val = EMPTY;
				T->eq = T->inf;
				T->inf = NULL;	
			}
			else if(T->sup != NULL){
				T->val = EMPTY;
				T->eq = T->sup;
				T->sup = NULL;
			}
			else {
				free(T);
				T = NULL;
			}
		}

		return T;

	}	

	else {
		if(*word < T->key){
			T->inf = del_HTrie(word, T->inf);
		}
		else if(*word > T->key){
			T->sup = del_HTrie(word, T->sup);
		}
		else{
			T->eq = del_HTrie(++word, T->eq);
		}

		if(T->inf == NULL && T->sup == NULL && T->eq == NULL){
			free(T);
			T = NULL;
		}

		else if(T->eq == NULL && T->inf != NULL){
			T->eq = T->inf;
			T->inf = NULL;
		}
		else if(T->eq == NULL && T->sup != NULL){
			T->eq = T->sup;
			T->sup = NULL;
		}

		return T;

	}


}

int search_HTrie(char * word, HTrie * T){

	if(T == NULL){
		return FALSE;
	}
	else if(strcmp(word,"") == 0){
		if(T->val == NON_EMPTY){
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else {
		if(*word < T->key)
			return search_HTrie(word, T->inf);
		else if(*word > T->key)
			return search_HTrie(word, T->sup);
		else
			return search_HTrie(++word, T->eq);


	}

}

int count_words_HTrie(HTrie * T){
	if(T == NULL){
		return 0;
	}
	else {
		if(T->val == EMPTY)
			return count_words_HTrie(T->eq) 
				+ count_words_HTrie(T->inf) 
				+ count_words_HTrie(T->sup);
		else
			return 1 + count_words_HTrie(T->eq) 
				+ count_words_HTrie(T->inf) 
				+ count_words_HTrie(T->sup);
	}
}

int count_null_HTrie(HTrie * T){
	if(T == NULL)
		return 1;
	else {
		return count_null_HTrie(T->eq)
			+ count_null_HTrie(T->inf);
		+ count_null_HTrie(T->sup);
	}
}

int height_HTrie(HTrie * T){

	if(T == NULL)
		return 0;
	else 
		return 1 + max_3(height_HTrie(T->inf), 
				height_HTrie(T->eq),
				height_HTrie(T->sup));


}

void inside_average(HTrie * T, int * level, int * count, int curr_level);

double average_level_HTrie(HTrie * T){
	int  level = 0, count = 0, curr_level = 1;
	inside_average(T, &level, &count, curr_level);
	if(count == 0) return 0.0;
	return (double) level / count;
}

void inside_average(HTrie * T, int * level, int * count, int curr_level){
	if(T == NULL) return;
	(*level) += curr_level;
	(*count)++;
	if(T->inf != NULL)
		inside_average(T->inf, level, count, curr_level + 1);
	if(T->eq != NULL)
		inside_average(T->eq, level, count, curr_level + 1);
	if(T->sup != NULL)
		inside_average(T->sup, level, count, curr_level + 1);
}


int count_prefix_HTrie(char * prefix, HTrie * T){

	if(strcmp(prefix, "") == 0){
		return count_words_HTrie(T);
	}
	if(*prefix < T->key)
		return count_prefix_HTrie(prefix, T->inf);
	else if (*prefix > T->key)
		return count_prefix_HTrie(prefix, T->sup);
	else
		return count_prefix_HTrie(++prefix, T->eq);
}


int count_nodes_HTrie(HTrie * T){
	if(T == NULL){
		return 0;
	}

	else 
		return 1 + count_nodes_HTrie(T->inf)
			+ count_nodes_HTrie(T->eq)
			+ count_nodes_HTrie(T->sup);
}


void inside_list_words(HTrie * T, word_list ** list, char * word);

word_list * list_words_HTrie(HTrie * T){

	word_list * list = (word_list *) malloc(sizeof(word_list));
	list->next = NULL;
	inside_list_words(T, &list, "");

	return list;	

}

void inside_list_words(HTrie * T, word_list ** list, char * word){
	int n;
	char * new_word;
	int i;

	if(T == NULL){
		return;
	}
	n = strlen(word);
	new_word = (char *) malloc(sizeof(char) * (n + 1));

	for(i = 0; i < n; i++){
		new_word[i] = word[i];
	}
	new_word[i] = T->key;

	if(T->val == NON_EMPTY){
		add_word_list(new_word, list);
	}

	inside_list_words(T->eq, list, new_word);
	inside_list_words(T->inf, list, word);
	inside_list_words(T->sup, list, word);

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
	else{
		if(T->inf == NULL && T->eq == NULL && T->sup == NULL)
			return 1;
		else 
			return (width(T->inf) + width(T->eq) + width(T->sup));
	}
}

int width_left(HTrie * T){

	if(T == NULL){
		return 0;
	}
	else { 
		return width_left(T->eq) + width(T->inf);
	}
}

int width_right(HTrie * T){
	if(T == NULL){
		return 0;
	}
	else {
		return width_right(T->eq) + width(T->sup);
	}
}

void inside_plot_file(HTrie * T, int x, int y){
	if(T == NULL)
		return;
	printf("%c %d %d\n", T->key, x, y);
	inside_plot_file(T->inf, x - (width_left(T->eq) + width_right(T->inf) + 1) * D_X, y + D_Y);

	printf("%c %d %d\n", T->key, x, y);
	inside_plot_file(T->eq, x, y + D_Y);

	printf("%c %d %d\n", T->key, x, y);

	inside_plot_file(T->sup, x + (width_right(T->eq) + width_left(T->sup)+ 1) * D_X, y + D_Y);

	printf("\n");

}

HTrie * add_file_HTrie(char * file_name, HTrie * T){
	FILE * file = fopen(file_name, "r");
	char * buffer;
	int i;
	if(file == NULL){
		fprintf(stderr,"fopen failed : %s\n", file_name);
		return NULL;
	}
	buffer = malloc(sizeof(char) * 128);
	for(i = 0; i < 128; i++) buffer[i] = '\0';
	while(fscanf(file,"%s", buffer) != EOF){
		T = add_HTrie(buffer, T);
		for(i = 0; i < 128; i++) buffer[i] = '\0';
	}
	fclose(file);
	fprintf(stderr,"Added %s\n", file_name);
	return T;
}


HTrie * del_file_HTrie(char * file_name, HTrie * T){

	FILE * file = fopen(file_name, "r");
	char * buffer;
	int i;
	if(file == NULL){
		fprintf(stderr,"fopen failed : %s\n", file_name);
		return NULL;
	}
	buffer = malloc(sizeof(char) * 128);
	for(i = 0; i < 128; i++) buffer[i] = '\0';
	while(fscanf(file,"%s", buffer) != EOF){
		T = del_HTrie(buffer, T);	
		for(i = 0; i < 128; i++) buffer[i] = '\0';
	}
	fclose(file);
	return T;
}


HTrie * add_directory_HTrie(char * dir_name, HTrie * T){

	DIR * dir = opendir(dir_name);
	struct dirent * entry;
	char path [256];
	if(dir == NULL){
		fprintf(stderr,"opendir failed\n");
		return NULL;
	}
	while((entry = readdir(dir))){
		if(!strcmp(entry->d_name, "."))
			continue;
		if(!strcmp(entry->d_name, ".."))
			continue;

		strcpy(path, dir_name);
		strcat(path, "/");
		strcat(path, entry->d_name);
		T = add_file_HTrie(path, T);

	}
	closedir(dir);
	return T;

}

HTrie * del_directory_HTrie(char * dir_name, HTrie * T){

	DIR * dir = opendir(dir_name);
	struct dirent * entry;
	char path [256];
	if(dir == NULL){
		fprintf(stderr,"opendir failed\n");
		return NULL;
	}
	while((entry = readdir(dir))){
		if(!strcmp(entry->d_name, "."))
			continue;
		if(!strcmp(entry->d_name, ".."))
			continue;

		strcpy(path, dir_name);
		strcat(path, "/");
		strcat(path, entry->d_name);
		T = del_file_HTrie(path, T);

	}
	closedir(dir);
	return T;
}

void inside_HTrie_to_BRTree(HTrie * H, BRTree * B, char * word){

	char * new_word;
	int n;
	int i;
	if(H == NULL){
		return;
	}
	n = strlen(word);
	new_word = (char *) malloc(sizeof(char) * (n + 1));
	for(i = 0; i < n; i++){
		new_word[i] = word[i];
	}
	new_word[i] = H->key;

	if(H->val == NON_EMPTY){
		B = add_BRTree(new_word, B);
	}

	inside_HTrie_to_BRTree(H->eq, B, new_word);
	inside_HTrie_to_BRTree(H->inf, B, word);
	inside_HTrie_to_BRTree(H->sup, B, word);
}

BRTree * HTrie_to_BRTree(HTrie * H){

	BRTree * B = empty_BRTree();
	inside_HTrie_to_BRTree(H,B,"");
	return B;
}

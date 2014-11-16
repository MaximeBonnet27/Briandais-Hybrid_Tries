#include "BRTree.h"

BRTree * empty_BRTree(){
	BRTree * new_BR = (BRTree *) malloc(sizeof(BRTree));
	new_BR->key = '\0';
	new_BR->child = NULL;
	new_BR->next = NULL;
	return new_BR;
}

int is_empty(BRTree * T){
	if(T == NULL ||(T->key == '\0' && T->child == NULL && T->next == NULL)){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BRTree * new_BRTree(char key, BRTree * child, BRTree * next){
	BRTree * new_BR = (BRTree *) malloc(sizeof(BRTree));
	new_BR->key = key;
	new_BR->child = child;
	new_BR->next = next;
	return new_BR;
}

BRTree * build_BRTree(char * word){
	if(strcmp(word,"\0") == 0){
		return empty_BRTree();
	}
	else{
		return new_BRTree(first(word),build_BRTree(end(word)), NULL);
	}

}
BRTree * add_BRTree(char * word, BRTree * T){
	if(is_empty(T)){
		if(strcmp(word,"\0") == 0){
			free(word);	
			return T;
		}
		return build_BRTree(word);
	}
	if(strcmp(word,"\0") == 0){
		if(T->key == '\0'){
			free(word);
			return T;
		}
		return new_BRTree('\0', NULL, T);

	}
	if(first(word) - T->key < 0){
		return new_BRTree(first(word), build_BRTree(end(word)), T);
	}else if(first(word) - T->key > 0){
		T->next = add_BRTree(word, T->next);
		return T;
	}else{
		// check if we're the last letter of the word
		if(is_empty(T->child)){
			if(strcmp(end(word),"\0") == 0)
				return T;
			return new_BRTree(T->key, 
					new_BRTree('\0', NULL, 
						build_BRTree(end(word))), 
					T->next);
		}
		T->child = add_BRTree(end(word), T->child);
		return T;
	}
}	


BRTree * del_BRTree(char * word, BRTree * T){

	if(T == NULL){
		return NULL;
	}
	if(is_empty(T) && strcmp(word, "") == 0){
		return T->next;
	}
	if(T->key == first(word)){
		BRTree * child = del_BRTree(end(word), T->child);
		if(child == NULL){
			return T->next;
		}
		else {	
			return new_BRTree(T->key, child, T->next);
		}
	}
	else if(T->key > first(word)){
		return T;
	}
	else {
		return new_BRTree(T->key, T->child, del_BRTree(word, T->next));
	}	

}

int search_BRTree(char * word, BRTree * T){
	if(strcmp(word, "") == 0){
		return is_empty(T);
	}
	else if(is_empty(T)) return FALSE;
	if(first(word) < T->key) return FALSE;
	else if(first(word) == T->key) return search_BRTree(end(word), T->child);
	else return search_BRTree(word, T->next);
}

void print_BRTree(BRTree * T){
	if(T == NULL) return;
	if(T->key == '\0')
		printf("\\0\n");
	else
		printf("%c\n", T->key);
	print_BRTree(T->child);
	print_BRTree(T->next);

}


int count_words_BRTree(BRTree *T){
	if(T == NULL)
		return 0;
	if(T->key == '\0'){
		return 1 + count_words_BRTree(T->next);
	}
	return count_words_BRTree(T->child) + count_words_BRTree(T->next);
}

int count_null_BRTree(BRTree * T){

	if(T == NULL)
		return 1;
	if(is_empty(T))
		return 2;
	return count_null_BRTree(T->child) + count_null_BRTree(T->next);
}


int height_BRTree(BRTree * T){

	if(is_empty(T)) return 0;
	return max(1 + height_BRTree(T->child), height_BRTree(T->next));
}

void inside_average(BRTree * T, int * level, int * count, int curr_level);

double average_level_BRTree(BRTree * T){
	int  level = 0, count = 0, curr_level = 1;
	inside_average(T, &level, &count, curr_level);
	if(count == 0) return 0.0;
	return (double) level / count;
}

void inside_average(BRTree * T, int * level, int * count, int curr_level){
	if(T == NULL) return;
	(*level) += curr_level;
	(*count)++;
	if(T->child != NULL)
		inside_average(T->child, level, count, curr_level + 1);
	if(T->next != NULL)
		inside_average(T->next, level, count, curr_level);
}

BRTree * add_file_BRTree(char * file_name, BRTree * T){

	FILE * file = fopen(file_name, "r");
	if(file == NULL){
		fprintf(stderr,"fopen failed : %s\n", file_name);
		return NULL;
	}

	char * buffer = malloc(sizeof(char) * 128);
	int i;
	for(i = 0; i < 128; i++) buffer[i] = '\0';
	while(fscanf(file,"%s", buffer) != EOF){
		T = add_BRTree(buffer, T);	
		for(i = 0; i < 128; i++) buffer[i] = '\0';
	}
	fclose(file);
	fprintf(stderr,"Added %s\n", file_name);
	return T;
}

BRTree * add_directory_BRTree(char * dir_name, BRTree * T){

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
		T = add_file_BRTree(path, T);

	}
	closedir(dir);
	return T;

}




int count_nodes_BRTree(BRTree * T){
	if(T == NULL){
		return 0;
	}

	else 
		return 1 + count_nodes_BRTree(T->child) + count_nodes_BRTree(T->next);
}

int count_prefix_BRTree(char * prefix, BRTree * T){

	if(strcmp(prefix, "") == 0){
		return count_words_BRTree(T);
	}
	if(first(prefix) < T->key)
		return 0;
	else if (first(prefix) > T->key)
		return count_prefix_BRTree(prefix, T->next);
	else
		return count_prefix_BRTree(end(prefix), T->child);



}


void free_BRTree(BRTree * T){
	if(T == NULL)
		return;
	else{
		free_BRTree(T->child);
		free_BRTree(T->next);
		free(T);
	}
}	

void inside_list_words(BRTree * T, word_list ** list, char * word);

word_list * list_words(BRTree * T){

	word_list * list = (word_list *) malloc(sizeof(word_list));
	list->word = "";	
	list->next = NULL;
	inside_list_words(T, &list, "");

	return list;	

}

void inside_list_words(BRTree * T, word_list ** list, char * word){

	if(T == NULL){
		return;
	}
	int n = strlen(word);
	char * new_word = (char *) malloc(sizeof(char) * (n + 1));
	int i;
	for(i = 0; i < n; i++){
		new_word[i] = word[i];
	}
	new_word[i] = T->key;

	if(T->key == '\0'){
		add_word_list(new_word, list);
	}

	inside_list_words(T->child, list, new_word);

	inside_list_words(T->next, list, word);

}


void add_word_list(char * word, word_list ** list){

	word_list * new = (word_list *) malloc(sizeof(word_list));
	new->word = word;
	new->next = *list;
	*list = new;


}

void print_word_list(word_list * list){
	while(list != NULL){
		printf("%s\n", list->word);
		list = list->next;
	}
}


BRTree * merge_BRTree(BRTree * T1, BRTree * T2){

	if(T1 == NULL)
		return T2;
	if(T2 == NULL)
		return T1;

	if(T2->key < T1->key){
		return new_BRTree(T2->key, T2->child, merge_BRTree(T1, T2->next));
	}
	else if(T2->key > T1->key){
		return new_BRTree(T1->key, T1->child, merge_BRTree(T1->next, T2));
	}
	else{
		return new_BRTree(T1->key, merge_BRTree(T1->child, T2->child),
				merge_BRTree(T1->next, T2->next));
	}

}

BRTree * del_file_BRTree(char * file_name, BRTree * T){

	FILE * file = fopen(file_name, "r");
	if(file == NULL){
		fprintf(stderr,"fopen failed : %s\n", file_name);
		return NULL;
	}
	char * buffer = malloc(sizeof(char) * 128);
	int i;
	for(i = 0; i < 128; i++) buffer[i] = '\0';
	while(fscanf(file,"%s", buffer) != EOF){
		T = del_BRTree(buffer, T);	
		for(i = 0; i < 128; i++) buffer[i] = '\0';
	}
	fclose(file);
	return T;
}

int inside_plot_file(BRTree * T, long x, long y, int next);
void make_plot_file_BRTree(BRTree * T){

	inside_plot_file(T, 0, 0, 0);	

}

int inside_plot_file(BRTree * T, long x, long y, int next){

	if(T == NULL){
		return 0;
	}

	if(next == 1){
		if(T->key == '\0'){
			printf(". %ld %ld\n\n", x, y);
		}
		else
			printf("%c %ld %ld\n\n",T->key, x, y);
	}
	if(T->key == '\0'){
		printf(". %ld %ld\n", x, y);
	}
	else
		printf("%c %ld %ld\n",T->key, x, y);

	int width_child = inside_plot_file(T->child, x, y + D_Y, 0);
	width_child = width_child < 10 ? 10 : width_child;
	printf("\n");


	if(T->key == '\0'){
		printf(". %ld %ld\n", x, y);
	}
	else
		printf("%c %ld %ld\n",T->key, x, y);

	return (width_child) + inside_plot_file(T->next, (x + width_child), y, 1);

}
BRTree * del_directory_BRTree(char * dir_name, BRTree * T){

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
		T = del_file_BRTree(path, T);

	}
	closedir(dir);
	return T;



}

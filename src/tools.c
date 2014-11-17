#include "tools.h"

char first(char * string){
	return string[0];
}

char * end(char * string){
	int n = strlen(string);
	char * new_string = (char *) malloc(sizeof(char) * n);
	int i;
	for(i = 0; i < n; i++){
		new_string[i] = string[i + 1];
	}
	return new_string;
}

int max (int a, int b){
	return a > b ? a : b;
}

int max_3(int a, int b, int c){

	if(a > b){
		if(a > c) return a;
		return c;
	}else {
		if(b > c) return b;
	}	return c;

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




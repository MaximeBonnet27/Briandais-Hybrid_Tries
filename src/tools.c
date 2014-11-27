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
	/* Add the word at the beginning of the
	 * list, that's not exactly what we want..
	 */
	/*word_list * new = (word_list *) malloc(sizeof(word_list));
	new->word = word;
	new->next = *list;
	*list = new;
	*/

	/* Add the word at the end of the list
	 */
	word_list * temp;
	word_list * new = (word_list *) malloc(sizeof(word_list));
	new->word = word;
	temp = *list;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new;

}

void print_word_list(word_list * list){
	while(list != NULL){
		printf("%s\n", list->word);
		list = list->next;
	}
}

void free_word_list(word_list * list){
	word_list * tmp = list;
	while(list != NULL){
		tmp = list;
		list = list->next;
		free(tmp);
	}
}




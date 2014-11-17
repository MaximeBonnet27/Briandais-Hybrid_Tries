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


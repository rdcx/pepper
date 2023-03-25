#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum token_response {
	found,
	notfound
};

enum token_type {
	token_notfound,
	token_variable,
	token_value,
	token_assignment,
	token_end
};


enum token_type parse_token(char *tok, char ch) {
	if (tok == NULL) {
		tok = malloc(sizeof(char *));
	}
	int len = strlen(tok);
	char* newstr = malloc((len * sizeof(char)) + sizeof(char));
		
	for (int i = 0; i < len; i++) {
		newstr[i] = tok[i];
	}
	
	newstr[len] = ch;	
	tok = newstr;
	
	if (strcmp(tok, "=") == 0) {
		return token_assignment;
	}

	if (strcmp(tok, ";") == 0) {
		return token_end;	
	}

	if (strcmp(tok, "$") == 0) {
		return token_variable;
	}

	printf("NOT FOUND (%s), len (%ld) \n\n", tok, strlen(tok));
	return token_notfound;
}

struct node {
	enum token_type type;
	struct node * next;
};

void token_type_debug(enum token_type tt) {
	switch (tt) {
	case token_variable:
		printf("variable found\n");
		break;
	case token_assignment:
		printf("assignment found\n");
		break;
	case token_end:
		printf("end found\n");
		break;
	}
}

int main(int argc, char* argv) {

	FILE* fp = fopen("./main.p", "r");
	
	char ch;

	char* text = malloc(sizeof(char*));
	struct node * n = malloc(sizeof(struct node *));
	struct node * base_node = n;
	char * tok;
	do {

		ch = fgetc(fp);
			
		enum token_response res;
		res = parse_token(tok, ch);
		
		token_type_debug(res);	
		
		if (res != token_notfound) {
			n->next = malloc(sizeof(struct node *));
			n = n->next;
			tok = malloc(sizeof(char *));
		}
	} while (ch != EOF);
}

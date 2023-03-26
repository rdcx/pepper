#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 0
#define DEBUG_PRINT(x) do { if (DEBUG) { printf("\n%s\n", x); } }

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

int is_variable(char *tok) {
	
	int len = strlen(tok);

	// A variable must be a minimum of 1 character after the $
	if (len < 2) {
		return 0;
	}

	// A variable must start with $
	if (tok[0] != *"$") {
		return 0;
	}

	// A variable must end with either a space ; or )
	if (tok[len - 1] != *" " && tok[len - 1] != *";" && tok[len-1] != *")" && tok[len-1] != *",") {
		printf("Variable does not end with either space ; ) ,)\n");
		return 0;
	}

	// First variable name character must be alpha
	if (!isalpha(tok[1])) {
		printf("First character is not alpha\n");
		return 0;
	}

	// all characters following must be alphanum
	for (int i = 1; i < len - 1; i++) {
		if (!isalnum(tok[i])) {
			printf("All variable name chars are not alpha numeric\n");
			return 0;
		}
	}

	return 1;
}

enum token_type parse_token(char *tok, char ch) {
	int len = strlen(tok);
	char* newstr = malloc((len * sizeof(char)) + sizeof(char));
		
	for (int i = 0; i < len; i++) {
		newstr[i] = tok[i];
	}
	
	newstr[len] = ch;	
	strcpy(tok, newstr);
	
	if (is_variable(tok) == 1) {
		return token_variable;
	}
	
	if (strcmp(tok, "=") == 0) {
		return token_assignment;
	}

	if (strcmp(tok, ";") == 0) {
		return token_end;	
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
		if (tok == NULL) {
			tok = malloc(sizeof(char *));
		}

		res = parse_token(tok, ch);
		
		token_type_debug(res);	
		
		if (res != token_notfound) {
			n->next = malloc(sizeof(struct node *));
			n = n->next;
			tok = malloc(sizeof(char *));
		}
	} while (ch != EOF);
}

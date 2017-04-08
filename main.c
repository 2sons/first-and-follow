#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int number;
	char * c;
} Body;

typedef struct {
	int number;
	Body * list;
} Production;

int main()
{
	int variables[256] = {0};
	int terminals[256] = {0};
	Production productions[256];
	int i;
	int j;
	getInput(variables, terminals, productions);
/*
	for (i = 0; i < 256; i++) {
		if (variables[i]) {
			printf("%c ", i);
		}
	}
	printf("\n");
	for (i = 0; i < 256; i++) {
		if (terminals[i]) {
			printf("%c ", i);
		}
	}
	printf("\n");
	for (i = 0; i < 256; i++) {
		if (productions[i].number) {
			for (j = 0; j < productions[i].number; j++) {
				printf("%c -> %s\n", i, productions[i].list[j].c);
			}

		}
	}
*/
	computeFirst(variables, terminals, productions);
	return 0;
}

int computeFirst(int * variables, int * terminals, Production * productions)
{
	int i;
	int j;
	int k;
	char symbol;
	printf("First\n");
	for (i = 0; i < 256; i++) {
		//if it is a terminal
		if (variables[i]) {
			char first[256] = {0};
			firstOf(variables, terminals, productions, i, first);
			//display first of the terminal
			printf("%c -> { ", i);
			if (first[0]) {
				printf("epsilon ");
			}
			for (j = 1; j < 256; j++) {
				if (first[j]) {
					printf("%c ", j);
				}
			}
			printf("}\n");
		}
	}
	return 0;
}

int firstOf(int * variables, int * terminals, Production * productions, int symbol, char * first)
{
	int lookup;
	int j;
	int k;
	//printf("%c -> { ", symbol);
	for (j = 0; j < productions[symbol].number; j++) {
		for (k = 0; k < productions[symbol].list[j].number; k++) {
			lookup = productions[symbol].list[j].c[k];
			if (variables[lookup]) {
					;
					/* if not nullable find first of 
					*/
					firstOf(variables, terminals, productions, lookup, first);
					if (!isNullable(productions[lookup])) {
						/*break the loop*/
						break;
					}
			} else if (terminals[lookup]) {
				first[lookup] = 1;
				break;
				//printf("%c ", lookup);
			} else if (lookup == '\0') {
				first[lookup] = 1;
			} else{
				printf("error -> %d symbol neither a terminal nor a variable", lookup);
			}
		}
		//when the loop completes it means the body is nullable
		if (k == productions[symbol].list[j].number) {
			first[0] = 1;
		}
	}
	//printf("}\n");
	return 0;
}

int isNullable(Production production) {
	int i;
	for (i = 0; i < production.number; i++) {
		if (production.list[i].number && (production.list[i].c[0] == '\0')) {
			return 1;
		}
	}
	return 0;
}

int getInput(int * variables, int * terminals, Production productions[256])
{
	int i;
	int j;
	int c;
	int numVariables;
	int numTerminals;
	int numProductions;
	char head;
	char body[50];//just an assumption for input length
	printf("Variables: ");
	scanf(" %d", &numVariables);
	for (i = 0; i < numVariables; i++) {
		scanf(" %c", &c);
		variables[c] = 1;
	}
	printf("Terminals: ");
	scanf(" %d", &numTerminals);
	for (i = 0; i < numTerminals; i++) {
		scanf(" %c", &c);
		terminals[c] = 1;
	}
	/*initialize production array*/
	for (i = 0; i < 256; i++) {
		productions[i].number = 0;
		productions[i].list= NULL;
	}
	printf("Number of Productions: ");
	scanf(" %d", &numProductions);
	for (i = 0; i < numProductions; i++) {
		scanf(" %c %s", &head, body);
		if (variables[head]) {
			productions[head].number++;
			productions[head].list = (Body *) realloc(productions[head].list, productions[head].number * sizeof(Body));
			productions[head].list[productions[head].number - 1].number = 0;
			productions[head].list[productions[head].number - 1].c = NULL;
			for (j = 0; j < strlen(body); j++) {
				productions[head].list[productions[head].number - 1].number++; 
				productions[head].list[productions[head].number - 1].c = (char *) realloc(productions[head].list[productions[head].number - 1].c, productions[head].list[productions[head].number - 1].number * sizeof(char));
				if (variables[body[j]] || terminals[body[j]]) {
					productions[head].list[productions[head].number - 1].c[productions[head].list[productions[head].number - 1].number - 1]  = body[j];
				} else {
					//this character is treated as a null character (which is neither in variables nor terminals)
					productions[head].list[productions[head].number - 1].c[productions[head].list[productions[head].number - 1].number - 1]  = '\0';
				}
			}
		}
	}
	return 0;
}

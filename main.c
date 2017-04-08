#include <stdio.h>

int main()
{
	int variables[256] = {0};
	int terminals[256] = {0};
	int * productions[256][2];
	int i;
	getInput(variables, terminals, productions);
/*	for (i = 0; i < 256; i++) {
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
*/
	return 0;
}

int getInput(int * variables, int * terminals, int * productions[256][2])
{
	int i;
	int c;
	int numVariables;
	int numTerminals;
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
	return 0;
}

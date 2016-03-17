#define NAME_LENGTH 10 // see ISO 7372:2005 page 62

#include <stdio.h>
#include <string.h>

int get_name(char name[]);

int main() {
	char player1[NAME_LENGTH + 1];
	char player2[NAME_LENGTH + 1];
	short int ai = 0; // for now, disable the AI here
	
	do {
		printf("Player 1 name: ");
	} while (get_name(player1));
	printf("Hello, %s!\n\n", player1);

	if (!ai) {
		do {
			printf("Player 2 name: ");
		} while (get_name(player2));
		printf("Hello, %s!\n\n", player2);
	}

	return 0;
}

int get_name(char name[]) {
	char input[NAME_LENGTH + 2];
	fgets(input, NAME_LENGTH + 2, stdin);
	if (input[strlen(input) - 1] != '\n') { // user must've input too much!
		printf("[ERROR] Invalid input, name too long! (maximum length %d characters)\n", NAME_LENGTH);
		while (getchar() != '\n'); // clear input buffer
		return 1;
	} else { // null terminate
		input[strlen(input) - 1] = '\0';
		strcpy(name, input);
		return 0;
	}
}
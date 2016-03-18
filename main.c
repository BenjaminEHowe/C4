#define NAME_LENGTH 10 // see ISO 7372:2005 page 62

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_grid(char grid[], unsigned short int gridsize);

int get_name(char name[]);

int main() {
	short int ai = 0; // for now, disable the AI here
	char player1[NAME_LENGTH + 1];
	char player2[NAME_LENGTH + 1];

	unsigned short int gridsize = 7;
	// allocate an array of length gridsize^2
	char *grid = malloc(sizeof(char) * gridsize * gridsize);
	// fill the array with spaces
	for (int i = 0; i < gridsize * gridsize; i++) {
		grid[i] = ' ';
	}
		
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

	display_grid(grid, gridsize);

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

void display_grid(char grid[], unsigned short int gridsize) {
	for (int i = 0; i < gridsize * gridsize; i++) {
		printf("|%c", grid[i]);
		if (i % gridsize == gridsize - 1) {
			printf("|\n");
		}
	}
	for (int i = 0; i < gridsize; i++) {
		printf("--");
	}
	printf("-\n");
	return;
}
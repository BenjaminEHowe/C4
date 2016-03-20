#define NAME_LENGTH 70 // see ISO 7372:2005 page 62

// see http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOUR_RED     "\x1b[31m"
#define ANSI_COLOUR_GREEN   "\x1b[32m"
#define ANSI_COLOUR_YELLOW  "\x1b[33m"
#define ANSI_COLOUR_BLUE    "\x1b[34m"
#define ANSI_COLOUR_MAGENTA "\x1b[35m"
#define ANSI_COLOUR_CYAN    "\x1b[36m"
#define ANSI_COLOUR_RESET   "\x1b[0m"

const char colour[7][8] = { ANSI_COLOUR_RESET,  ANSI_COLOUR_YELLOW,
						    ANSI_COLOUR_RED, ANSI_COLOUR_GREEN,
						    ANSI_COLOUR_BLUE, ANSI_COLOUR_CYAN,
						    ANSI_COLOUR_MAGENTA };

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_int.h"
#include "clear.h"
#include "win_checks.h"

bool check_draw(unsigned short int position);
bool check_win(unsigned short int position);
void display_grid();
int get_name(char name[]);
unsigned short int play(unsigned short int current_player);


// the grid (and gridsize) should be global as most functions will need them
char* grid; // will br used with malloc later
unsigned short int gridsize = 0;

int main() {
	short int ai = 0; // for now, disable the AI here
	unsigned short int current_player;
	char player[6][NAME_LENGTH + 1];
    unsigned short int players = 0;
	unsigned short int position;
	unsigned short int turn = 0;
	unsigned short int won = USHRT_MAX;

	clear();
    
    do {
        printf("Number of players: ");
		if (scanf("%hu", &players) != 1) {
			printf("[ERROR] That doesn't look like an integer!\n");
		} else if (gridsize > 6) {
			printf("[ERROR] The maximum number of players is 6!\n");
		}

		if (players == 0) { // if we're going around again...
			while (getchar() != '\n');
		}

	} while (players == 0);
    
    for (int i = 0; i < players; i++) {
        do {
            printf("Player %d name: ", (i + 1));
        } while (get_name(player[i]));
    }    
    
	do {
        printf("Grid size: ");
		if (scanf("%hu", &gridsize) != 1) {
			printf("[ERROR] That doesn't look like an integer!\n");
		} else if (gridsize > 255) {
			printf("[ERROR] The gridsize must be less than 255!\n");
		}

		if (gridsize != 0) { // try to allocate memory for an array of chars length gridsize^2
        		grid = (char*) malloc(sizeof(char) * gridsize * gridsize);
        		if (grid == NULL) {
                    printf("[ERROR] Couldn't allocate memory - try a smaller grid size?\n");
                    gridsize = 0;
                } else {                
                    // fill the array with spaces
                    for (int i = 0; i < gridsize * gridsize; i++) {
                            grid[i] = ' ';
                    }
                }
		}

		if (gridsize == 0) { // if we're going around again...
			while (getchar() != '\n');
		}

	} while (gridsize == 0);
    
	clear();
	display_grid();
	printf("\n"); // leave one blank line between the grid and question

	while(won == USHRT_MAX) {
		current_player = turn % players;
		printf("%s%s%s, which column would you like to play in? ", colour[current_player + 1], player[current_player], colour[0]);
		position = play(current_player);
		if (check_win(position)) {
			won = current_player;
		} else if (check_draw(position)) {
			won = USHRT_MAX - 1;
		}
		turn++;
		clear();
		display_grid();
		printf("\n"); // leave one blank line between the grid and question
	}

	if (won == USHRT_MAX - 1) { // draw!
		printf("It's a draw!\n");
	} else { // player `won` won!
		printf("%s%s%s won!\n", colour[won + 1], player[won], colour[0]);
	}

	printf("\nPress any key to continue...\n");
	while (getchar() != '\n'); while (getchar() != '\n');
	clear();
	return 0;
}

bool check_draw(unsigned short int position) {
	if (position < gridsize) { // if the player played in the top row
		// check if the grid is full
		for (int i = 0; i < gridsize; i++) {
			if (grid[i] == ' ') {
				break;
			}
			if (i == gridsize - 1) { // if we've got this far in the last iteration
				return true;
			}
		}
	}
	return false;
}

bool check_win(unsigned short int position) {
	unsigned short int x = position % gridsize;
	unsigned short int y = position / gridsize;
	char player_token = grid[position];

	if (y <= gridsize - 4) {
		if (check_down(x, y, player_token)) {
			return true;
		}
	}

	if (check_horizontal(x, y, player_token)) {
		return true;
	}

	if (check_diagonal('+', x, y, player_token)) {
		return true;
	}

	if (check_diagonal('-', x, y, player_token)) {
		return true;
	}

	return false;
}

void display_grid() {
	/* note: the top left slot is grid[0] and bottom right is
	grid[gridsize * gridsize - 1]. So, to find out if there is space in
	column x, simply check that grid[x] is free (== ' '). */
	for (int i = 0; i < gridsize; i++) {
		printf(" %d", i + 1);
	}
	printf("\n");
	for (int i = 0; i < gridsize * gridsize; i++) {
		if (grid[i] == ' ') { // don't render empty spaces, just print them
			printf("| ");
		}
		else { // actually do rendering
			printf("|%sO%s", colour[char_to_int(grid[i])], colour[0]);
		}
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

int get_name(char name[]) {
	char input[NAME_LENGTH + 2];
	fgets(input, NAME_LENGTH + 2, stdin);
	if (input[strlen(input) - 1] != '\n') { // user must've input too much!
		printf("[ERROR] Invalid input, name too long! (maximum length %d characters)\n", NAME_LENGTH);
		while (getchar() != '\n'); // clear input buffer
		return 1;
	} else if (strlen(input) == 1) {
		printf("[ERROR] A name is required!\n");
		return 1;
	} else { // null terminate
		input[strlen(input) - 1] = '\0';
		strcpy(name, input);
		return 0;
	}
}

unsigned short int play(unsigned short int current_player) {
	short int status = 0;
	unsigned short int position = 0;
	do {
		if (scanf("%hu", &position) != 1) {
			printf("[ERROR] That doesn't look like an integer!\n");
		} else if (position < 1 || position > gridsize) {
			printf("[ERROR] That column doesn't seem to exist!\n");
		} else if (grid[position - 1] != ' ') {
			printf("[ERROR] That column is full!\n");
		} else {
			status = 1;
		}

		if (status == 0) { // if we're going around again...
			printf("Which column would you like to play in? ");
			while (getchar() != '\n');
		}
	} while (status == 0);

	// put the counter in the lowest possible slot (biggest number)
	int i = gridsize * (gridsize - 1) + (position - 1);
	while (1) {
		if (grid[i] == ' ') { // if this slot is free, go for it
			grid[i] = int_to_char(current_player + 1); // because player[0] is "Player 1"
			break;
		} else { // otherwise, try one slot higer
			i = i - gridsize;
		}
	}

	return i;
}

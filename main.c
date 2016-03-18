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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short int char_to_int(char var);
void clear();
void display_grid();
int get_name(char name[]);
char int_to_char(unsigned short int var);
void play(unsigned short int current_player);
void set_console_pos(int x, int y);

// the grid (and gridsize) should be global as most functions will need them
char grid[1]; // allocate an array of size 1 for now, so it can be resized
unsigned short int gridsize;

int main() {
	short int ai = 0; // for now, disable the AI here
	unsigned short int current_player;
	char player[2][NAME_LENGTH + 1];
	unsigned short int position = 0;
	unsigned int turn = 0;
	unsigned int won = 0;

	gridsize = 7;
	// allocate an array of length gridsize^2
	realloc(*grid, sizeof(char) * gridsize * gridsize);
	// fill the array with spaces
	for (int i = 0; i < gridsize * gridsize; i++) {
		grid[i] = ' ';
	}
		
	do {
		printf("Player 1 name: ");
	} while (get_name(player[0]));
	printf("Hello, %s!\n\n", player[0]);

	if (!ai) {
		do {
			printf("Player 2 name: ");
		} while (get_name(player[1]));
		printf("Hello, %s!\n\n", player[1]);
	}

	while(!won) {
		current_player = turn % 2;
		clear();
		display_grid();
		printf("\n"); // leave one blank line between the grid and question
		printf("%s, which column would you like to play in? ", player[current_player]);
		play(current_player);
		if (won == 0) { // if we're going around again, clear for the next move
			clear();
			turn++;
		}
	}

	return 0;
}

unsigned short int char_to_int(char var) {
	// note: only works for the range '1' to '6' inclusive
	switch (var) {
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	default:
		return 0;
	}
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

char int_to_char(unsigned short int var) {
	// note: only works for the range 1 to 6 inclusive
	switch (var) {
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		default:
			return 'X';
	}
}

void play(unsigned short int current_player) {
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

	return;
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
		} else { // actually do rendering
			char str[16];
			strcpy(str, colour[char_to_int(grid[i])]);
			strcat(str, "O");
			strcat(str, colour[0]);
			printf("|%s", str);
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

// see: http://stackoverflow.com/a/5920028
#ifdef _WIN32 // windows implementation of set_console_pos
#include <windows.h>

// see: https://web.archive.org/web/20111216170632/http://www.adrianxw.dk/SoftwareSite/Consoles/Consoles2.html
void set_console_pos(int x, int y) {
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void clear() {
	system("cls");
}
#elif __unix__ // sane (probably linux) implementation using ANSI
#include <cstdlib> // windows does this for you (with respect to system())

// see: https://web.archive.org/web/20150906020006/http://rosettacode.org/wiki/Terminal_control/Cursor_positioning#C.2FC.2B.2B
void set_console_pos(int x, int y) {
	printf("\033[%d;%dH", y + 1, x + 1);
}

void clear() {
	system("clear");
}
#endif
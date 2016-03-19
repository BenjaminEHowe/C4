#include "win_checks.h"

#include <stdbool.h>

extern char* grid[];
extern unsigned short int gridsize;

bool check_diagonal(char type, unsigned short int x, unsigned short int y, char player_token) {
	unsigned short int in_a_row = 0;
	unsigned short int position;

	short int min_x;
	if (x >= 4) {
		min_x = -3;
	}
	else {
		min_x = -x;
	}

	short int max_x;
	if (x < gridsize - 4) {
		max_x = 3;
	}
	else {
		max_x = (gridsize - 1) - x;
	}

	short int min_y;
	if (y >= 4) {
		min_y = -3;
	}
	else {
		min_y = -y;
	}

	short int max_y;
	if (y < gridsize - 4) {
		max_y = 3;
	}
	else {
		max_y = (gridsize - 1) - y;
	}

	short int min;
	if (min_x > min_y) {
		min = min_x;
	}
	else {
		min = min_y;
	}

	short int max;
	if (max_x < max_y) {
		max = max_x;
	}
	else {
		max = max_y;
	}

	for (short int i = min; i <= max; i++) {
		if (type == '+') {
			position = (x + i) + (y + i) * gridsize;
		}
		else {
			position = (x - i) + (y + i) * gridsize;
		}
		if (grid[position] == player_token) {
			in_a_row++;
		}
		else {
			in_a_row = 0;
		}
		if (in_a_row == 4) {
			return true;
		}
	}

	return false;
}

bool check_down(unsigned short int x, unsigned short int y, char player_token) {
	unsigned short int in_a_row = 0;

	for (unsigned short int i = 0; i < 4; i++) {
		if (grid[x + (y + i) * gridsize] == player_token) {
			in_a_row++;
		} else {
			in_a_row = 0;
		}
		if (in_a_row == 4) {
			return true;
		}
	}
	return false;
}

bool check_horizontal(unsigned short int x, unsigned short int y, char player_token) {
	unsigned short int in_a_row = 0;

	unsigned short int min_x;
	if (x >= 4) {
		min_x = x - 3;
	} else {
		min_x = 0;
	}

	unsigned short int max_x;
	if (x < gridsize - 4) {
		max_x = x + 3;
	} else {
		max_x = gridsize - 1;
	}

	for (x = min_x; x <= max_x; x++) {
		if (grid[x + y * gridsize] == player_token) {
			in_a_row++;
		}
		else {
			in_a_row = 0;
		}
		if (in_a_row == 4) {
			return true;
		}
	}

	return false;
}
#include "win_checks.h"

#include <stdbool.h>

extern char* grid;
extern unsigned short int gridsize;

bool check_diagonal(char type, unsigned short int x, unsigned short int y, char player_token) {
	unsigned short int in_a_row = 0;
	unsigned short int position;

	for (short int i = -3; i < 4; i++) {
		if (type == '+') {
			if (check_valid_coord(x + i) && check_valid_coord(y + i)) { // if this is a valid coordinate
				position = (x + i) + (y + i) * gridsize;
			} else {
				if (!(check_valid_coord(x + i - 1) && check_valid_coord(y + i - 1))) { // if the previous coordinate was also invalid
					continue;
				} else { // previous coordinate was valid
					break;
				}
			}
		} else {
			if (check_valid_coord(x + i) && check_valid_coord(y - i)) { // if this is a valid coordinate
				position = (x + i) + (y - i) * gridsize;
			} else {
				if (!(check_valid_coord(x + i - 1) && check_valid_coord(y - i + 1))) { // if the previous coordinate was also invalid
					continue;
				} else { // previous coordinate was valid
					break;
				}
			}
		}
		
		if (grid[position] == player_token) {
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

bool check_valid_coord(unsigned short int coord) {
	if (0 <= coord && coord < gridsize) {
		return true;
	} else {
		return false;
	}
}

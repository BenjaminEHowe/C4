#include "char_int.h"

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
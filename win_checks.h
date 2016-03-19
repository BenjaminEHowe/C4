#ifndef WIN_CHECKS_H
#define WIN_CHECKS_H

#include <stdbool.h>

bool check_down(unsigned short int x, unsigned short int y, char player_token);
bool check_horizontal(unsigned short int x, unsigned short int y, char player_token);
bool check_diagonal(char type, unsigned short int x, unsigned short int y, char player_token);

#endif
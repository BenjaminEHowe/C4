#include "clear.h"

#ifdef _WIN32

void clear() {
	system("cls");
}

#elif __unix__ // sane (probably linux) implementation using ANSI
#include <cstdlib> // windows does this for you (with respect to system())

void clear() {
	system("clear");
}

#endif
#include "clear.h"

#include <stdlib.h>	

#ifdef _WIN32

void clear() {
	system("cls");
}

#elif __unix__ // sane (probably linux) implementation using ANSI

void clear() {
	system("tput reset");
}

#endif

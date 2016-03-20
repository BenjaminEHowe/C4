#include "clear.h"

#ifdef _WIN32

void clear() {
	system("cls");
}

#elif __unix__ // sane (probably linux) implementation using ANSI
#include <stdlib.h>

void clear() {
	system("tput reset");
}

#endif

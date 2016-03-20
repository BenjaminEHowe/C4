all :
	gcc -std=c11 main.c char_int.c clear.c win_checks.c -o C4

clean :
	rm C4

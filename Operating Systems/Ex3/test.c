/* * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Timothy Russell-Wagner                *
 * COP4600 Exercise 4 - Consecutive.c            *
 * Checks a file of ints, with one per line,     *
 * and prints all lines where the previous line  *
 * is not exactly one less than the current line *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>

int main(int argc, char* argv[]) {
	int i = 0;
	for (i = 0; i < argc; i++){
		printf("%s\n",argv[i]);

	}
	return 0;
}

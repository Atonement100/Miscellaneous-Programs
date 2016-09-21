/* * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Timothy Russell-Wagner                *
 * COP4600 Exercise 4 - Consecutive.c            *
 * Checks a file of ints, with one per line,     *
 * and prints all lines where the previous line  *
 * is not exactly one less than the current line *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>

int main(void) {
	int OldInt, NewInt;
	int LineNum = 2;
	scanf("%d",&OldInt);
	while(scanf("%d", &NewInt) != EOF){
	   if (NewInt != OldInt + 1) printf("%5d: %d\n", LineNum, NewInt);
	   OldInt = NewInt;
	   LineNum++;
	}
	return 0;
}
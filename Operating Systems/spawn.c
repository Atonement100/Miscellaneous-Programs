/* * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Timothy Russell-Wagner                *
 * COP4600 Exercise 4 - spawn.c 	             *
 * Run as ./spawn <n> "<program> <args>"		 *
 * Forks n children, and each runs				 *
 * <program> with <args>						 *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Too few arguments passed\n");
		return -1;
	}
	char* ProgramToExec = strtok(argv[2]," ");
	char** Args = malloc(1 * sizeof(*Args));	

	if(Args){
		char* ArgToAdd = strtok(NULL," ");	
		int ArgIndex = 0;
		int Subargs = 1;
		while(ArgToAdd != NULL){
			if (!Args[ArgIndex]){
				//We allocate only Subargs+1 space each time, instead of
				//something like twice as much space as before etc.
				//because the space required here should not exceed 
				//a few args.
				char** TempArgs = realloc(Args, (Subargs+1)*sizeof(*Args));
				if (!TempArgs) return -1;
				
				Args = TempArgs;
			}
			
			Args[ArgIndex] = ArgToAdd;
			ArgIndex++;
			ArgToAdd = strtok(NULL," ");
			Subargs++;
		}
		if (!Args[ArgIndex]) {
			char** TempArgs = realloc(Args, (Subargs+1)*sizeof(*Args));
			Args = TempArgs;
		}
		Args[ArgIndex] = NULL;	
	}

	int NumToSpawn = strtol(argv[1], NULL, 10);
	int pid;
	while (NumToSpawn > 0){
		pid = fork();
		if (pid == 0){
			int x = 0;
		 	x = execv(ProgramToExec, Args);
			printf("%d",x);
		}
		NumToSpawn--;
	}
	if (pid != 0) wait(NULL);
	return 0;

}

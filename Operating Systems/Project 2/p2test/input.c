#include <unistd.h>
#include <stdio.h>
#include <time.h>
int main(void)
{
	int pid;
	pid = fork();
	if (pid !=0){
		int returnv =	plog_state_start(pid);
		char c;
		while(1){
			scanf("%d",c);
			printf("%d",c);
		}
	}	
	return 0;
}

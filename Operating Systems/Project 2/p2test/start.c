#include <unistd.h>
#include <stdio.h>
int main(void)
{
	int pid;
	pid = fork();
	if (pid !=0){
		int returnv =	plog_state_start(pid);
		for(int i = 0 ; i < 100000; i ++){
			printf("%d",i);
		}
	}	
	return 0;
}

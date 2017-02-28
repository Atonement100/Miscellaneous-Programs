#include <unistd.h>
#include <stdio.h>
#include <time.h>
int main(void)
{
	int pid;
	pid = fork();
	if (pid !=0){
		int returnv =	plog_state_start(pid);
		time_t now = time(0);
		int i;
		while (time(0) - now < 30){
		i++;
		printf("%d",i);
		}
	}	
	return 0;
}

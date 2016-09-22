#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int pid;
	long ct = -2, tt = -2;	

	pid = fork();
	pid = fork();
	get_plog_byPID(pid,&ct,&tt);
	printf("pid: %d, ct: %ld, tt: %ld\n", pid,ct,tt);

	wait();
	if (pid == 0){
		exit(1);
		printf("exited");
	}

	get_plog_byPID(pid,&ct,&tt);
	printf("pid: %d, ct: %ld, tt: %ld\n", pid,ct,tt);





	return 0;
}

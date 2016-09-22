#include <unistd.h>
#include <stdio.h>
int main(void)
{
	int pid;
	long ct = -2, tt = -2;	

	pid = -1;
if(	get_plog_byindex(pid, &ct, &tt) == 3)printf("good\n");

	printf("pid:%d ct:%ld tt:%ld\n", pid, ct, tt);

	pid = 1024;
	if(get_plog_byindex(pid, &ct, &tt) == 3)printf("good\n");
	printf("pid:%d ct:%ld tt:%ld\n", pid, ct, tt);

	pid = 1231242;	
	if(get_plog_byPID(pid, &ct, &tt) == 2) printf("good\n");return 0;
	printf("pid:%d ct:%ld tt:%ld\n", pid, ct, tt);
	return 0;
}

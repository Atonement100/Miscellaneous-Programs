#include <lib.h>
#include <unistd.h>
#include <stdio.h>
int main(void)
{
	int pid;
	message m;
	int test = 3;
	m.m2_i1 = test;
	_syscall(PM_PROC_NR, LOGPROCS, &m);
	printf("this is working? %d\n", m.m2_i1);
	return 0;
}

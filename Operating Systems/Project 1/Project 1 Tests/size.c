#include <unistd.h>
#include <stdio.h>
int main(void)
{
	int pid;
	pid = get_plog_size();
	printf("returned: %d\n",pid);
	return 0;
}

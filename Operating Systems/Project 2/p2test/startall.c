#include <unistd.h>
#include <stdio.h>
int main(void)
{
	int returnv =	plog_state_start(0);
	printf("returned %d\n", returnv);
	return 0;
}

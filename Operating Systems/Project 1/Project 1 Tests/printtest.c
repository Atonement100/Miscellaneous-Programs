#include <unistd.h>

int main(void)
{
	pid_t pid;
	start_plog();
	pid = fork();	
	pid = fork();
	stop_plog();
	return 0;
}

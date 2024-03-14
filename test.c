#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

// ctrl + D = SIGQUIT
// EOF, exits program

// ctrl + C = SIGINT
// interrupts program, goes back to top level
// (in shell = new cmd line/ emty prompt)

void ctrl_c(int signum)
{
	write(1, "U can't kill me\n", 15);
}

int main()
{
	signal(SIGINT, ctrl_c);
	while (1)
	{
		printf("send me signals\n");
		sleep(1);
	}
    return (0);
}

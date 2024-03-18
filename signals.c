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

// write preferable than printf

// Ctrl-D isn't a signal. It closes stdin, which causes the read() to return 0, which is interpreted as EOF.

// killall ./a.out

void	sigusr1(int signum)
{
	printf("sigusr1 signal: %d\n", signum);
}

void	ctrl_c(int signum)
{
	printf("\nctrl c signal: %d\n", signum);
	write(1, "U can't kill me\n", 16);
}

int main()
{
	signal(SIGINT, ctrl_c);
	signal(SIGUSR1, sigusr1);
	printf("my pid: %d\n", getpid());
	printf("to use sigusr type kill -SIGUSR1 <pid>\n");
	while (1)
	{
		printf("send me signals\n");
		sleep(1);
	}
    return (0);
}

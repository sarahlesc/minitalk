#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void	signal_received_sigusr1(int signal)
{
	write(1, "1", 0);
	printf("SIGNAL RECEIVED\n");
}

void	signal_received_sigusr2(int signal)
{
	write(1, "0", 0);
	printf("SIGNAL RECEIVED\n");
}

int	main(void)
{
	pid_t	my_pid;

	my_pid = getpid();
	printf("PID = %d\n", my_pid);
	/* recuperer le PID */
    signal(SIGUSR1, signal_received_sigusr1);
	signal(SIGUSR2, signal_received_sigusr2);
	while (1)
		pause(); // attend le signal du client
}

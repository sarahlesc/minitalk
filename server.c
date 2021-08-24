#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	print_message(char *msg)
{
	ft_putstr_fd(msg, 1);
	free(msg);
}

void	signal_received()
{
	printf("SIGNAL RECEIVED\n");
}

int	main(void)
{
	pid_t my_pid;

	/* recuperer le PID */
	my_pid = getpid();
	printf("PID = %d\n", my_pid);
    signal(SIGUSR1, );
    return (0);

	while (1)
		pause(); // attend le signal du client
}

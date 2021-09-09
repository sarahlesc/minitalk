#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void	send_signals(int pid, char *message)
{
	int	i;
	int	shift;

	shift = -1;
	i = -1;
	while (message[++i] != '\0')
	{
		while (++shift < 8)
		{
			if (message[i] & 0x80 >>shift)
				kill(pid, SIGUSR2); // envoi du 0
			else
				kill(pid, SIGUSR1); // envoi du 1
			usleep(2);
		}
	}
}

int		main(int argc, char **argv)
{
	int		pid;

	if (argc != 3)
	{
		printf("Invalid arguments\n");
		exit (0);
	}
	pid = atoi(argv[1]);
	if (pid > 2147483647 || pid <= 0)
	{
		printf("ERROR\nInvalid form of PID\n");
		exit (0);
	}
	printf("PID = %d\n", pid);
	send_signals(pid, argv[2]);
	return (0);
}

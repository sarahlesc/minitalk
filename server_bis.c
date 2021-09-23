
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/include/libft.h"

void	write_pid(pid_t	pid)
{
	char	*str_pid;

	str_pid = ft_itoa(pid);
	printf("PID = %s\n", str_pid);
	printf("=================================");
	printf("=================================\n");
	free(str_pid);
}

void	ft_putstr(const char *str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i] != '\0')
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
}

char	*print_message(char *message)
{
	ft_putstr(message);
	free(message);
	return (NULL);
}

char	*ft_straddc_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_straddc(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_straddc_first(c));
	add = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!add)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		add[i] = str[i];
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

void	handler_sigusr(int signum, siginfo_t *info, void *context)
{
  static unsigned char	c = 0;
  static int	bits = 7;
	static	int	client_pid = 0;
	static char	*message = 0;

	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (signum == SIGUSR2)
		c |= (1UL << bits);
	bits--;
	if (bits == -1)
	{
		if (c)
			message = ft_straddc(message, c);
		else
		{
			message = print_message(message);
			printf("\n");
			kill(client_pid, SIGUSR2);
		}
		bits = 7;
		c = 0;
	}
}

/*
** The Sigaction structure is used to change the normal behaviour of the
** system when receiving signals. In this case, instead of finishing the
** program as soon as it receives the signal (normal behavior), it will
** call the sig_handles function.
**
** sa_flags: Allows changing the behavior of the handling process.
** To use the sa_sigaction handler, you must put SA_SIGINFO here.
** SA_SIGINFO stores information about the signal. It has 3 parameters
** (the signal, the pointer to the info about the signal and the context)
**
** The pid is retrieved and put in the menu for the client.
**
** The server waits for the signals from the client to come.
*/

int	main(void)
{
	pid_t	my_pid;
	struct sigaction	sa_signal;

	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_sigaction = handler_sigusr;
	my_pid = getpid();
	write_pid(my_pid);
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	while (1)
		pause();
}

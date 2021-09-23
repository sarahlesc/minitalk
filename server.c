/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:27 by slescure          #+#    #+#             */
/*   Updated: 2021/09/23 18:56:28 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/include/libft.h"

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

void	write_pid(pid_t	pid)
{
	char	*str_pid;

	str_pid = ft_itoa(pid);
	ft_putstr("PID = ");
	ft_putstr(str_pid);
	ft_putstr("\n=================================");
	ft_putstr("=================================\n");
	free(str_pid);
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

	add = malloc(sizeof(char) * 2);
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
	add = malloc(sizeof(char) * (ft_strlen(str) + 2));
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

void	handler_sigusr(int signal, siginfo_t *info, void *context)
{
  static unsigned char	car = 0xFF;
  static int	shift = 0;
	static	int	pid = 0;
	static char	*message = 0;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (signal == SIGUSR2 && shift < 8)
		car = car | 0x80 >> shift;
	else if (signal == SIGUSR1 && shift < 8)
		car = car ^ 0x80 >> shift;
	shift++;
	if (shift == 8)
	{
		if (car)
			message = ft_straddc(message, car);
		else
		{
			message = print_message(message);
			ft_putstr_fd("\n", 1);
			kill(pid, SIGUSR2);
		}
		shift = 0;
		car = 0xFF;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:27 by slescure          #+#    #+#             */
/*   Updated: 2021/09/28 09:21:31 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/include/libft.h"

char	*print_message(char *message)
{
	if (message == NULL)
		return (NULL);
	ft_putstr_fd(message, 1);
	free(message);
	ft_putstr_fd("\n", 1);
	return (NULL);
}

char	*ft_add_chara_first(char c)
{
	char	*add;

	add = malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_add_chara(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_add_chara_first(c));
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

/*
CONVERTIR LES SIGNAUX (BINAIRES) EN CARACTÈRES
On utilise OR (|) et XOR (^) pour réunir tous les 1 et 0 et ainsi
reconstituer le nombre.
En fonction du signal reçu (SIGUSR1 = 0, SIGUSR2 = 1), on compare
notre base 11111111 avec 10000000 :
- si c'est un 0, on utilise (^)
- si c'est un 1, on utilise (|)
Exemple :
01100001
1er chiffre : 0 --> 11111111 ^ 10000000 = 01111111
2e chiffre : 1 --> 01111111 | 01000000 = 01111111
3e chiffre : 1 --> 01111111 | 00100000 = 01111111
4e chiffre : 0 --> 01111111 ^ 00010000 = 01101111
etc...
*/

void	handler_sigusr(int signal, siginfo_t *info, void *context)
{
	static unsigned char	car = 0xFF;
	static int				shift = 0;
	static int				pid = 0;
	static char				*message = 0;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (signal == SIGUSR2 && shift < 8)
		car = car | 0x80 >> shift;
	else if (signal == SIGUSR1 && shift < 8)
		car = car ^ 0x80 >> shift;
	if (++shift == 8)
	{
		if (car)
			message = ft_add_chara(message, car);
		else
		{
			message = print_message(message);
			kill(pid, SIGUSR2);
		}
		shift = 0;
		car = 0xFF;
	}
}

int	main(void)
{
	pid_t				my_pid;
	struct sigaction	sa_signal;
	char				*str_pid;

	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_sigaction = handler_sigusr;
	my_pid = getpid();
	str_pid = ft_itoa(my_pid);
	ft_putstr_fd("PID = ", 1);
	ft_putstr_fd(str_pid, 1);
	ft_putstr_fd("\n___________________________________________________\n", 1);
	free(str_pid);
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	while (1)
		pause();
}

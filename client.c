/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:40:04 by slescure          #+#    #+#             */
/*   Updated: 2021/09/27 22:52:02 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/include/libft.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR2)
	{
		ft_putstr_fd("Message received\n", 1);
		exit(0);
	}
}

/*
This functions sends the null character to finish the string.
*/

void	finish_transmission(int pid)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

/*
CONVERTIR LES CARACTÈRES EN SIGNAUX VERS CLIENT.C
il faut donc envoyer 8 signaux pour representer les 8 bits de chaque caractere
depuis client vers serveur
pour les envoyer un par un, on utilise >> pour déplacer le bit vers la
droite et remplace par 0 sur son ancienne place
puis on compare notre caractère sous forme binaire avec
10000000 (0x80) avec (&) pour repérer les 1
Si le résultat avec (&) du caractère en binaire et de 0x80 donne 1, alors
on envoie le signal à SIGUSR1, si c'est un 0, on envoie SIGUSR2
Puis on >> 0x80 afin de bouger de 10000000 avec 01000000
Exemple :
01100001
01100001 & 10000000 = 0000000 --> on envoie donc 0
>> 10000000 = 010000000
01100001 & 010000000 = 010000000 --> on envoie 1
etc....
*/

void	send_signal(char *str, int server_pid)
{
	int	i;
	int	shift;

	i = 0;
	while (str[i])
	{
		shift = -1;
		while (++shift < 8)
		{
			if (str[i] & 0x80 >> shift)
			{
				if (kill(server_pid, SIGUSR2) == -1)
					exit(1);
			}
			else
			{
				if (kill(server_pid, SIGUSR1) == -1)
					exit(1);
			}
			usleep(50);
		}
		i++;
	}
	finish_transmission(server_pid);
}

/*
sa_flags: Allows changing the behavior of the handling process.
To use the sa_sigaction handler, you must put SA_SIGINFO here.
SA_SIGINFO stores information about the signal. It has 3 parameters
(the signal, the pointer to the info about the signal and the context)
*/

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa_signals;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (!pid || pid > 2147483647 || pid <= 0)
		{
			ft_putstr_fd("ERROR: invalid form of PID \n", 1);
			exit (0);
		}
		sa_signals.sa_flags = SA_SIGINFO;
		sa_signals.sa_sigaction = sig_handler;
		sigaction(SIGUSR1, &sa_signals, NULL);
		sigaction(SIGUSR2, &sa_signals, NULL);
		send_signal(argv[2], pid);
	}
	else
		ft_putstr_fd("ERROR: Invalid arguments\n", 1);
	return (0);
}

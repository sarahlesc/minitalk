/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:53:31 by slescure          #+#    #+#             */
/*   Updated: 2021/09/23 11:00:46 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/include/libft.h"

/*

SIGUSR1 = 1
SIGUSR2 = 0

*/

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

void	send_error(char *message)
{
	printf("ERROR\n%s\n", message);
	exit (0);
}

void	send_signals(int pid, char *message)
{
	int	i;
	int	shift;

	shift = -1;
	i = 0;
	while (message[i] != '\0')
	{
		while (++shift < 8)
		{
			if (message[i] & 0x80 >> shift)
			{
				if (kill(pid, SIGUSR1) == -1)
					send_error("Wrong pid");
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					send_error("Wrong pid");
			}
			usleep(300);
		}
		shift = -1;
		i++;
	}
	while (++shift < 8)
	{
		if ('\0' & 0x80 >> shift)
		{
			if (kill(pid, SIGUSR1) == -1)
				send_error("Wrong pid");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				send_error("Wrong pid");
		}
		usleep(300);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	struct sigaction	sa_signals;

	if (argc != 3)
		send_error("Invalid arguments");
	else
	{
		pid = ft_atoi(argv[1]);
		if (!pid)
		{
			printf("ERROR: invalid PID \n");
			return(EXIT_FAILURE);
		}
		sa_signals.sa_flags = SA_SIGINFO;
		sa_signals.sa_sigaction = sig_handler;
		sigaction(SIGUSR1, &sa_signals, NULL);
		sigaction(SIGUSR2, &sa_signals, NULL);
		send_signals(pid, argv[2]);
	return (0);
}

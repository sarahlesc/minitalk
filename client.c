/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:53:31 by slescure          #+#    #+#             */
/*   Updated: 2021/09/10 18:18:16 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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
				kill(pid, SIGUSR1);
			}
			else
			{
				kill(pid, SIGUSR2);
			}
			usleep(80);
		}
		shift = -1;
		i++;
	}
}

int	main(int argc, char **argv)
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

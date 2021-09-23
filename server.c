/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:53:52 by slescure          #+#    #+#             */
/*   Updated: 2021/09/21 21:46:54 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/include/libft.h"

/*

CONVERTIR LES SIGNAUX (BINAIRES) EN CARACTÈRES
On utilise OR (|) et XOR (^) pour réunir tous les 1 et 0 et ainsi
reconstituer le nombre.
En fonction du signal reçu (SIGUSR1 = 1, SIGUSR2 = 0), on compare
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

void	character_received(int signal)
{
	static char	car = 0xFF;
	static int	shift = 0;
	static int	i = 0;
	static char	*str = NULL;

	if (str == NULL)
	{
//		printf("ici ?\n");
		str = malloc(sizeof(char) * 2);
		if (str == NULL)
			exit (0);
	}
	if (signal == SIGUSR1 && shift < 8)
		car = car | 0x80 >> shift;
	else if (signal == SIGUSR2 && shift < 8)
		car = car ^ 0x80 >> shift;
	shift++;
	if (shift == 8)
	{
		i++;
		if (i == 1)
		{
			str[0] = car;
			str[1] = '\0';
		}
		else
			str = ft_strjoin(str, &car);
//		printf("str = %s\n", str);

//		write(1, &car, 1);
		if (car == '\0')
		{
//			printf("la ?\n");
//			printf("i = %i\n", i);
//			printf("ici ?\n");
			ft_putstr_fd(str, 1);
//			printf("%s", str);
			free (str);
			str = NULL;
			i = 0;
		}
		shift = 0;
		car = 0xFF;
	}
}

int	main(void)
{
	pid_t	my_pid;

	my_pid = getpid();
	printf("PID = %d\n", my_pid);
	signal(SIGUSR1, character_received);
	signal(SIGUSR2, character_received);
	while (1)
		pause();
}

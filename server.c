/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:53:52 by slescure          #+#    #+#             */
/*   Updated: 2021/09/16 16:18:45 by slescure         ###   ########.fr       */
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
	static t_double_list *str = NULL;

	if (signal == SIGUSR1 && shift < 8)
		car = car | 0x80 >> shift;
	else if (signal == SIGUSR2 && shift < 8)
		car = car ^ 0x80 >> shift;
	shift++;
	if (shift == 8)
	{
		if (car != '\0')
			ft_double_lstadd_back(&str, ft_double_lstnew(car));
//		printf("str->content = %c\n", str->content);
		if (car == '\0')
		{
			ft_double_lstfirst(str);
//			write(1, &str->content, 1);
			printf("\n");
	//		exit (0);
			while (str->next != NULL)
			{
				printf("ici ?\n");
				write(1, &str->content, 1);
				str = str->next;
			}
			write(1, &str->content, 1);
//			printf("ici5\n");
			ft_double_lstclear(&str, 0);
//			printf("ici6\n");
			str = NULL;
		}
		else
		{
			shift = 0;
			car = 0xFF;
		}
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

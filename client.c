/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:40:04 by slescure          #+#    #+#             */
/*   Updated: 2021/09/23 18:56:24 by slescure         ###   ########.fr       */
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
** This functions sends the null character to finish the string.
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
** This function converts each character into binary using bitwise operators,
** it sends each bit as a signal to the server. SIGUSR1 represents 0, SIGUSR2
** represents 1.
**
** When it finishes sending the whole converted string, it calls the function
** finish transmission, that will pass the null character.
*/

void send_signal(char *str, int server_pid)
{
   int   i;
   int   shift;

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
         usleep(30);
      }
      i++;
   }
  	finish_transmission(server_pid);
}

/*
** The main function handles the errors if not given a valid pid and/or 3
** arguments in the command line. If all necessary conditions are met, it
** converts the server pid to integer to be used by the program.
**
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
*/

int	main(int argc, char **argv)
{
	int	pid;
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

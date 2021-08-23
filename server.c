#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	print_message(char *msg)
{
	ft_putstr_fd(msg, 1);
	free(msg);
}

int	main(void)
{
	/* recuperer le PID */
	
	while (1)
		pause(); // attend le signal du client
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_print_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:44:31 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:44:33 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_print_list(t_double_list *lst)
{
	int	compt;

	compt = 0;
	if (lst == NULL)
		return ;
	while (lst->next != NULL)
	{
		printf("compt = %d content = %d\n", compt, lst->content);
		compt++;
		lst = lst->next;
	}
	printf("compt = %d content = %d\n", compt, lst->content);
}

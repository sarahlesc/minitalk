/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstadd_back.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:43:41 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:43:42 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_lstadd_back(t_double_list **alst, t_double_list *new)
{
	t_double_list	*temp;

	new->next = NULL;
	temp = *alst;
	if (temp == NULL)
	{
		new->previous = NULL;
		temp = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	new->previous = temp;
	temp->next = new;
}

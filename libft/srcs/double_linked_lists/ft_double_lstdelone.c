/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstdelone.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:44:05 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:44:07 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_lstdelone(t_double_list **lst, int pos)
{
	t_double_list	*temp;

	if (*lst == NULL || pos < 0)
		return ;
	temp = *lst;
	while (temp->previous != NULL)
		temp = temp->previous;
	if (pos == 0)
		case_first_node(lst);
	else if (pos == ft_double_lstsize(temp))
		case_last_node(lst);
}

void	case_first_node(t_double_list **lst)
{
	t_double_list	*temp_to_free;
	t_double_list	*temp;

	temp_to_free = *lst;
	if (temp_to_free->next == NULL)
	{
		*lst = NULL;
		free(temp_to_free);
		return ;
	}
	*lst = temp_to_free->next;
	temp = *lst;
	temp->previous = NULL;
	free(temp_to_free);
}

void	case_last_node(t_double_list **lst)
{
	t_double_list	*temp;

	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	temp = *lst;
	*lst = temp->previous;
	temp->previous->next = temp->previous;
	free(temp);
}

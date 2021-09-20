/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstcopy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:43:59 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:44:01 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_double_list	*ft_double_lstcopy(t_double_list *stack)
{
	t_double_list	*new;

	new = NULL;
	while (stack != NULL)
	{
		if (new == NULL)
			new = ft_double_lstnew(stack->content);
		else
			ft_double_lstadd_back(&new,
				ft_double_lstnew(stack->content));
		stack = stack->next;
	}
	return (new);
}

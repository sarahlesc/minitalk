/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstfirst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:44:11 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:44:13 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_double_list	*ft_double_lstfirst(t_double_list *lst)
{
	t_double_list	*new;

	if (lst == NULL)
		return (NULL);
	new = lst;
	while (new->previous != NULL)
		new = new->previous;
	return (new);
}

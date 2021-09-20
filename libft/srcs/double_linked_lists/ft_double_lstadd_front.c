/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstadd_front.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:43:47 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:43:48 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_lstadd_front(t_double_list **alst, t_double_list *new)
{
	new->previous = NULL;
	new->next = *alst;
	if (*alst != NULL)
		(*alst)->previous = new;
	*alst = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:48:07 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:48:08 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int		i;
	const char			*tempsrc;
	char				*tempdest;

	i = 0;
	tempsrc = src;
	tempdest = dst;
	if (tempsrc == (void *)0 && tempdest == (void *)0)
		return (NULL);
	while (i < n)
	{
		tempdest[i] = tempsrc[i];
		i++;
	}
	return (tempdest);
}

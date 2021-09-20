/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:48:20 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:48:21 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char						*tempdest;
	const char					*tempsrc;
	int							i;

	tempdest = dest;
	tempsrc = src;
	if (dest > src)
	{
		i = len - 1;
		while (i >= 0)
		{
			tempdest[i] = tempsrc[i];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}

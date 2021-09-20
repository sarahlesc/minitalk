/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:45:51 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:45:51 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int		i;
	unsigned char		*tempdest;
	unsigned const char	*tempsrc;

	i = 0;
	tempdest = dest;
	tempsrc = src;
	while (i < n)
	{
		tempdest[i] = tempsrc[i];
		if (tempsrc[i] == (unsigned char)c)
			return (&tempdest[i + 1]);
		i++;
	}
	return (NULL);
}

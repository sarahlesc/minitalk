/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:48:43 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:48:44 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned long	i;

	i = 0;
	if (c == '\0' && str[0] == '\0')
		return ((char *)str);
	while (i <= ft_strlen(str))
	{
		if (c == str[i])
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

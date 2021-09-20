/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:48:56 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:48:56 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int						i;
	unsigned int						j;
	char								*rslt;

	rslt = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (rslt == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		rslt[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		rslt[i] = s2[j];
		i++;
		j++;
	}
	rslt[i] = '\0';
	return (rslt);
}

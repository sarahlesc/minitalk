/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:10:26 by slescure          #+#    #+#             */
/*   Updated: 2021/09/21 19:22:24 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoin_bis(char *s1, char *s2)
{
	unsigned int						i;
	unsigned int						j;
	char								*rslt;
	char								*cpy;

	cpy = malloc(sizeof(char) * (ft_strlen(s1) + 1))
	if (cpy == NULL)
		return (NULL);
	rslt = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (rslt == NULL)
		return (NULL);
	i = 0;
	while (*s1[i] != '\0')
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
	printf("result = %s\n", rslt);
	free (&s1);
	return (rslt);
}

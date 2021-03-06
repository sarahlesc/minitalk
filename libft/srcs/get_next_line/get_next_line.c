/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:44:46 by slescure          #+#    #+#             */
/*   Updated: 2021/06/02 13:44:48 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	return_value(int char_read, char **temp)
{
	if (char_read < 0)
		return (-1);
	if (char_read > 0)
		return (1);
	free(*temp);
	*temp = NULL;
	return (0);
}

int	error_case(int fd, char **line, char **temp, char **buf)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL || read(fd, *temp, 0) < 0)
		return (-1);
	if (*temp == NULL)
	{
		*temp = malloc(sizeof(char));
		if (*temp == NULL)
			return (-1);
		*temp[0] = '\0';
	}
	*buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (*buf == NULL)
		return (-1);
	return (0);
}

char	*copy_to_join(char *temp, char *buf)
{
	char				*cpy;

	cpy = temp;
	temp = ft_strjoin(cpy, buf);
	free(cpy);
	return (temp);
}

char	*copy_to_get_temp(char *temp)
{
	char				*cpy;

	cpy = temp;
	temp = get_temp(temp, '\n');
	free(cpy);
	return (temp);
}

int	get_next_line(int fd, char **line)
{
	char				*buf;
	static char			*temp = NULL;
	int					char_read;

	char_read = 1;
	if (error_case(fd, line, &temp, &buf) < 0)
		return (-1);
	if (!(ft_strchr(temp, '\n')))
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		while (char_read > 0)
		{
			buf[char_read] = '\0';
			temp = copy_to_join(temp, buf);
			if (ft_strchr(buf, '\n'))
				break ;
		}
	}
	free(buf);
	*line = ft_trim(temp, '\n');
	temp = copy_to_get_temp(temp);
	return (return_value(char_read, &temp));
}

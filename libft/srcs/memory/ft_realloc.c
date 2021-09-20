/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:25:31 by slescure          #+#    #+#             */
/*   Updated: 2021/09/20 17:12:21 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

typedef struct	s_chunk t_chunk;

struct		s_chunk
{
  t_chunk	*prev;
  t_chunk	*next;
  bool		is_free;
  size_t	size;
  void		*address;
};

t_chunk		*find_chunk(t_chunk *tmp, void *ptr)
{
  if (ptr == NULL)
    return (NULL);
  while (tmp != NULL)
    {
      if (tmp->address == ptr)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

void		*realloc(void *ptr, size_t size)
{
	void		*new_ptr;
	t_chunk	*old;
	t_chunk	*new;

	new_ptr = malloc(size)
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	old = find_chunk(g_heap_start, ptr);
	new = find_chunk(g_heap_start, new_ptr);
	if (old == NULL || new == NULL)
		return (new_ptr);
	ft_memcpy(new, old);
	free(ptr);
	return (new_ptr);
}

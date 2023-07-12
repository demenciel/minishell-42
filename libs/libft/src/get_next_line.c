/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:53:36 by rofontai          #+#    #+#             */
/*   Updated: 2023/04/21 21:23:36 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

void	*calloc_ptr(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	f_bzero(ptr, (count * size));
	return (ptr);
}

void	f_bzero(void *s, size_t n)
{
	size_t	i;
	char	*temp;

	if (!s)
		return ;
	i = 0;
	temp = (char *)s;
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}

int	lenstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*free_ft(char *str)
{
	if (str)
		free(str);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (0);
	save = ft_read(fd, save);
	if (!save)
		return (free_ft(save));
	line = extract_line(save, '\n');
	save = crop_save(save, '\n');
	if (!line)
		return (free_ft(save));
	return (line);
}

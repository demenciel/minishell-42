/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:19:36 by rofontai          #+#    #+#             */
/*   Updated: 2023/03/24 11:29:38 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_MEMCHR finds the first occurrence of c in s.
	We also need to specify to the function the size of the memory block
	in which to search.*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*temp;

	if (!s)
		return (0);
	temp = (char *)s;
	i = 0;
	while (i < n)
	{
		if (temp[i] == (char)c)
			return (&temp[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:18:45 by rofontai          #+#    #+#             */
/*   Updated: 2023/03/24 11:29:41 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_MEMCMP compares the contents of the two blocks (s1 and s2).
	n specifies the number of bytes on which to compare the two blocks.*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	if (!s1 || !s2)
		return (0);
	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if ((temp1[i] > temp2[i]) || (temp1[i] < temp2[i]))
			return (temp1[i] - temp2[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:27:13 by rofontai          #+#    #+#             */
/*   Updated: 2023/03/24 11:29:46 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_MEMMOVE copies n of src to dest.
	Accepts that the two memory areas can overlap. */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*temp;

	if (!dst || !src)
		return (0);
	temp = (char *)src;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			((char *)dst)[len] = temp[len];
		}
	}
	while (i < len)
	{
		((char *)dst)[i] = temp[i];
		i++;
	}
	return (dst);
}

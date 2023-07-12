/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:00:09 by romainfonta       #+#    #+#             */
/*   Updated: 2023/03/24 11:30:08 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_STRDUP allocate a new memory area via the malloc function
	in order to copy the initial character string (s1)*/
char	*ft_strdup(const char *s1)
{
	size_t		len_s;
	char		*dest;

	if (!s1)
		return (0);
	len_s = ft_strlen(s1) + 1;
	dest = (char *)malloc(len_s);
	if (dest == 0)
		return (0);
	return (ft_memcpy(dest, s1, len_s));
}

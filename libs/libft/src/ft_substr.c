/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:00:59 by romainfonta       #+#    #+#             */
/*   Updated: 2023/03/24 11:30:39 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_SUBSTR allocates memory with malloc and returns a string of
characters from the string 's'. This new channel starts at
the index 'start' and has the maximum size 'len'*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	len_s;

	i = 0;
	len_s = ft_strlen(s);
	if (start < len_s)
		while (i < len && s[start + i])
			i++;
	dest = (char *)malloc(i + 1);
	if (!dest)
		return (0);
	if (start >= len_s)
	{
		dest[0] = '\0';
		return (dest);
	}
	i = 0;
	while (i < len && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

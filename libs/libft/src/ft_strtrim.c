/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:38:27 by rofontai          #+#    #+#             */
/*   Updated: 2023/03/24 11:30:36 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_STRTRIM allocates memory with malloc and returns a copy of
the string 's1', without the characters specified in 'set' at
the beginning and at the end of the character string.*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		len_s1;
	char		*dest;

	i = 0;
	len_s1 = ft_strlen(s1);
	if (!len_s1)
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[len_s1 - 1] && ft_strchr(set, s1[len_s1 - 1]) && len_s1 > i)
		len_s1--;
	dest = malloc(sizeof(char) * (len_s1 - i + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, &s1[i], (len_s1 - i) + 1);
	return (dest);
}

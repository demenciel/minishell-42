/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:53:09 by romainfonta       #+#    #+#             */
/*   Updated: 2023/03/24 11:30:05 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_STRCHR finds the first occurrence of the character passed (c)
	in specific character string(s).*/
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	t;

	if (!s)
		return (0);
	i = 0;
	t = c;
	while (s[i] != t)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)&s[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:18:58 by romainfonta       #+#    #+#             */
/*   Updated: 2023/03/24 11:30:32 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_STRRCHR search the last occurrence of c in s.*/
char	*ft_strrchr(const char *s, int c)
{
	int		len_s;
	char	t;

	if (!s)
		return (0);
	t = c;
	len_s = ft_strlen(s);
	while (s[len_s] != t)
	{
		if (len_s == 0)
			return (0);
		len_s--;
	}
	return ((char *)&s[len_s]);
}

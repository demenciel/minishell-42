/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:12:45 by romainfonta       #+#    #+#             */
/*   Updated: 2023/03/24 11:29:14 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	len_n(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*number(char *s, int i, long nb)
{
	s[i--] = '\0';
	if (nb == 0)
	{
		s[0] = '0';
		return (s);
	}
	if (nb < 0)
	{
			s[0] = '-';
			nb *= -1;
	}
	while (nb > 0)
	{
		s[i--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (s);
}

/*FT_ITOA function coverts the integer n into a character string.*/
char	*ft_itoa(int n)
{
	char	*str;
	int		l;
	long	n_nb;

	n_nb = n;
	l = len_n(n_nb);
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (!str)
		return (0);
	return (number(str, l, n_nb));
}

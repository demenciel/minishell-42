/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:26:10 by romainfonta       #+#    #+#             */
/*   Updated: 2023/03/24 11:29:48 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_MEMSET filled b with len c.*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t		i;
	char		*temp;

	if (!b)
		return (0);
	temp = b;
	i = 0;
	while (i < len)
		temp[i++] = c;
	return (b);
}

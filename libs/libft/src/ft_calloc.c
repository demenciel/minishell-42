/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:39:18 by romainfonta       #+#    #+#             */
/*   Updated: 2023/07/11 09:14:09 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_CALLOC function shall allocate unused space for an array of
       count elements each of whose size in bytes is size.  The space
       shall be initialized to all bits 0.*/
void	*ft_calloc(size_t size, size_t count)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

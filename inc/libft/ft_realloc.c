/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:16:44 by acouture          #+#    #+#             */
/*   Updated: 2023/06/10 08:32:09 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief Reallocates a block of memory to a new size
 * @param ptr Pointer to the block of memory
 * @param size Size of the new memory block
 * @return A pointer to the new memory block.
*/
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (ptr != NULL)
	{
		if (original_size < new_size)
			ft_memcpy(new_ptr, ptr, original_size);
		else
			ft_memcpy(new_ptr, ptr, new_size);
		free(ptr);
	}
	return (new_ptr);
}

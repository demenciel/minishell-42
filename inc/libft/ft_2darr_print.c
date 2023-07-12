/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2darr_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:40:18 by acouture          #+#    #+#             */
/*   Updated: 2023/07/05 09:16:28 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Prints a 2d array
 * @param tb The 2d array to print
*/
void	ft_2darr_print(char **tb)
{
	int	i;

	i = 0;
	while (tb[i])
	{
		printf("%s\n", tb[i]);
		i++;
	}
}
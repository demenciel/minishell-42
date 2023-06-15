/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print2darr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:40:18 by acouture          #+#    #+#             */
/*   Updated: 2023/06/15 13:42:00 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Prints a 2d array
 * @param tb The 2d array to print
*/
void	print_tab2d(char **tb)
{
	int	i;

	i = 0;
	while (tb[i])
	{
		printf("%s\n", tb[i]);
		i++;
	}
	printf("\n\n");
}
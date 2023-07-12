/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:18:52 by rofontai          #+#    #+#             */
/*   Updated: 2023/07/10 21:38:07 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	**ft_free_tab_int(int **tabl, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
	return (0);
}

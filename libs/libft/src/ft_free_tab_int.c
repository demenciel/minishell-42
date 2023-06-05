/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:18:52 by rofontai          #+#    #+#             */
/*   Updated: 2023/05/31 08:27:24 by rofontai         ###   ########.fr       */
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
	return(0);
}
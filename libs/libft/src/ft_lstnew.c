/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:29:39 by rofontai          #+#    #+#             */
/*   Updated: 2023/03/24 11:29:33 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_LSTNEW allocate memory with malloc and return a new element.
	The member variable content is initialized using the value of the parameter
	(content). The 'next' variable is initialized to NULL*/
t_list	*ft_lstnew(void *content)
{
	t_list	*i;

	i = malloc(sizeof(t_list));
	if (!i)
		return (NULL);
	i->content = content;
	i->next = NULL;
	return (i);
}

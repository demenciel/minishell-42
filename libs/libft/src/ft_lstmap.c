/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:05:36 by rofontai          #+#    #+#             */
/*   Updated: 2023/03/24 11:29:30 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*FT_LSTMAP iterates over the 'lst' list and applies the 'f' function to
	the content of each element. Creates a new list resulting from
	the applications successive 'f'. The 'del' function is there to destroy
	the content of an element if necessary.*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	void	*cont;

	new = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		cont = ((*f)(lst->content));
		temp = ft_lstnew((cont));
		if (!temp)
		{
			ft_lstclear(&new, del);
			free(cont);
			return (new);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}

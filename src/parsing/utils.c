/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:49:49 by romain            #+#    #+#             */
/*   Updated: 2023/08/09 20:49:53 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_pars	*f_new_node(char *str)
{
	t_pars	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(t_pars), 1);
	if (!new)
		return (NULL);
	new->txt = str;
	new->next = NULL;
	return (new);
}

t_pars	*f_last_node(t_pars *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	f_addback_node(t_pars **cmd, t_pars *new)
{
	t_pars	*last;

	if (!cmd || !new)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	last = f_last_node(*cmd);
	last->next = new;
}

int	f_check_metachar(char c)
{
	if (c == 124 || c == 62 || c == 60 || c == 39 || c == 34 || c == 36
		|| c <= 32)
		return (1);
	else
		return (0);
}

char	*f_trimstr(char *s1, char c)
{
	size_t	i;
	size_t	len_s1;
	char	*dest;

	i = 0;
	len_s1 = ft_strlen(s1);
	if (!len_s1)
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(&c, s1[i]))
		i++;
	while (s1[len_s1 - 1] && ft_strchr(&c, s1[len_s1 - 1]) && len_s1 > i)
		len_s1--;
	dest = ft_calloc(sizeof(char), (len_s1 - i) + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s1[i], (len_s1 - i) + 1);
	return (dest);
}

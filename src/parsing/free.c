/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:40:17 by romain            #+#    #+#             */
/*   Updated: 2023/08/10 13:28:21 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	f_free_null_meta(t_meta *ms)
{
	if (ms->line)
		ms->line = f_freenull(ms->line);
	if (ms->com_temp)
		ms->com_temp = f_freenull(ms->com_temp);
	if (ms->in)
		ms->in = f_freenull(ms->in);
	if (ms->out)
		ms->out = f_freenull(ms->out);
	ms->i = 0;
	if (ms->list)
	{
		f_free_list(&ms->list);
		ms->list = NULL;
	}
	if (ms->comand)
	{
		f_free_comand(&ms->comand);
		ms->comand = NULL;
	}
	ms->error_flag = 0;
}

void	f_free_comand(t_comand **list)
{
	t_comand	*temp;

	if (!*list || !list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		ft_free_tab_char((*list)->com);
		free((*list)->stin);
		free((*list)->stout);
		free(*list);
		(*list) = temp;
	}
	*list = NULL;
}

void	f_free_list(t_pars **list)
{
	t_pars	*temp;

	if (!*list || !list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->txt);
		free(*list);
		(*list) = temp;
	}
	*list = NULL;
}

void	*f_freenull(void *str)
{
	if (str)
		free(str);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:51:32 by rofontai          #+#    #+#             */
/*   Updated: 2023/08/14 09:49:34 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_comand	*f_new_com(char *com, char *in, char *out)
{
	t_comand	*new;

	new = ft_calloc(sizeof(t_comand), 1);
	if (!new)
		return (NULL);
	if (com)
		new->com = ft_split(com, 29);
	else
		new->com = NULL;
	if (in)
		new->stin = ft_strdup(in);
	else
		new->stin = NULL;
	if (out)
		new->stout = ft_strdup(out);
	else
		new->stout = NULL;
	return (new);
}

void	f_zero_new_com(t_meta *ms)
{
	if (ms->com_temp != NULL)
	{
		free(ms->com_temp);
		ms->com_temp = NULL;
	}
	if (ms->in)
	{
		free(ms->in);
		ms->in = NULL;
	}
	if (ms->out)
	{
		free(ms->out);
		ms->out = NULL;
	}
}

t_comand	*f_last_com(t_comand *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	f_addback_com(t_comand **cmd, t_comand *new)
{
	t_comand	*last;

	if (!cmd || !new)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	last = f_last_com(*cmd);
	last->next = new;
}

void	f_split_pipes(t_meta *ms)
{
	t_pars	*temp;

	temp = ms->list;
	while (temp)
	{
		while (temp && temp->txt && temp->txt[0] != 124)
		{
			if (temp && temp->txt[0] == 62)
				f_cut_add_out(ms, &temp);
			else if (temp && temp->txt[0] == 60)
				f_cut_add_in(ms, &temp);
			else
				if (temp && temp->txt != NULL)
					f_add_com(ms, temp->txt);
			if (temp)
				temp = temp->next;
		}
		f_addback_com(&ms->comand, f_new_com(ms->com_temp, ms->in, ms->out));
		f_zero_new_com(ms);
		if (temp == NULL)
			break ;
		temp = temp->next;
	}
	f_free_list(&ms->list);
	ms->list = NULL;
}

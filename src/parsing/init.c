/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:03:46 by rofontai          #+#    #+#             */
/*   Updated: 2023/08/11 18:00:13 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_meta	*f_init_meta(void)
{
	static t_meta	*new;

	if (!new)
	{
		new = ft_calloc(sizeof(t_meta), 1);
		if (!new)
			return (NULL);
		new->list = NULL;
		new->com_temp = NULL;
		new->in = NULL;
		new->out = NULL;
		new->i = 0;
		new->line = NULL;
		new->comand = NULL;
		new->exit_status = 0;
		new->error_flag = 0;
	}
	return (new);
}

void	f_all_clean(t_meta *ms, char *msg)
{
	f_free_meta(ms);
	if (g()->export_list)
		ft_2darr_free(g()->export_list);
	if (g()->env_list)
		ft_2darr_free(g()->env_list);
	if (g()->in_fd > 2)
		close(g()->in_fd);
	if (g()->pid != NULL)
		free(g()->pid);
	clean_fd();
	if (msg)
	{
		printf("%s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	f_all_clean_exit(t_meta *ms, int nb)
{
	if (ms->line)
		free(ms->line);
	if (ms->comand)
		f_free_comand(&ms->comand);
	if (ms->com_temp)
		free(ms->com_temp);
	if (ms->in)
		free(ms->in);
	if (ms->out)
		free(ms->out);
	if (ms->list)
		f_free_list(&ms->list);
	if (ms)
		free(ms);
	if (g()->export_list)
		ft_2darr_free(g()->export_list);
	if (g()->env_list)
		ft_2darr_free(g()->env_list);
	if (g()->in_fd > 2)
		close(g()->in_fd);
	if (g()->pid)
		free(g()->pid);
	clean_fd();
	exit(nb);
}

void	f_free_exit_child(t_meta *ms, int nb)
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
	free(g()->pid);
	exit(nb);
}

void	f_free_meta(t_meta *ms)
{
	if (ms->line)
		free(ms->line);
	if (ms->comand)
		f_free_comand(&ms->comand);
	if (ms->com_temp)
		free(ms->com_temp);
	if (ms->in)
		free(ms->in);
	if (ms->out)
		free(ms->out);
	if (ms->list)
		f_free_list(&ms->list);
	if (ms)
		free(ms);
}

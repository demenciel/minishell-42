/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:17:50 by rofontai          #+#    #+#             */
/*   Updated: 2023/08/14 11:40:32 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	f_check_word(t_meta *ms)
{
	int		start;
	char	*temp;
	char	*add;

	start = ms->i;
	while (ms->line[ms->i] && f_check_metachar(ms->line[ms->i]) == 0)
		ms->i++;
	temp = ft_substr(ms->line, start, (ms->i - start));
	if (temp == NULL)
		return ;
	else if (start > 1 && f_check_metachar(ms->line[start - 1]) == 0)
	{
		add = ft_strjoin(f_last_node(ms->list)->txt, temp);
		f_last_node(ms->list)->txt = f_freenull(f_last_node(ms->list)->txt);
		f_last_node(ms->list)->txt = ft_strdup(add);
		add = f_freenull(add);
		temp = f_freenull(temp);
	}
	else
		f_addback_node(&ms->list, f_new_node(temp));
}

void	f_check_single_quote(t_meta *ms)
{
	int		start;
	char	*temp;

	start = ms->i++;
	while (ms->line[ms->i] && ms->line[ms->i] != 39)
		ms->i++;
	temp = ft_substr(ms->line, start, (ms->i - start) + 1);
	temp = f_pars_simple_quote(ms, temp);
	if (temp == NULL)
	{
		ms->i++;
		return ;
	}
	f_addback_node(&ms->list, f_new_node(temp));
	ms->i++;
}

char	*f_pars_simple_quote(t_meta *ms, char *txt)
{
	char	*temp;

	(void)ms;
	if (f_som_quote_simple(txt) != 2)
	{
		ms->exit_status = 1;
		ms->error_flag = 1;
		f_freenull(txt);
		return (NULL);
	}
	temp = f_trimstr(txt, 39);
	f_freenull(txt);
	return (temp);
}

int	f_size_list(t_pars *lst)
{
	int		count;
	t_pars	*temp;

	count = 0;
	temp = lst;
	if (temp == NULL)
		return (count);
	while (temp->next != NULL)
	{
		count++;
		temp = temp->next;
	}
	if (temp->next == NULL)
		count++;
	return (count);
}

void	f_new_check_dollar(t_meta *ms)
{
	int		start;
	char	*temp;
	char	*add;

	start = ms->i++;
	while (ms->line[ms->i] && f_check_env_dol(ms->line[ms->i]) == 1)
		ms->i++;
	temp = ft_substr(ms->line, start, (ms->i - start));
	temp = f_pars_new_dollar(ms, temp);
	if (temp == NULL)
		return ;
	else if (f_search_dollar(ms->line) == -1 && f_size_list(ms->list) > 1)
	{
		add = ft_strjoin(f_last_node(ms->list)->txt, temp);
		f_last_node(ms->list)->txt = f_freenull(f_last_node(ms->list)->txt);
		f_last_node(ms->list)->txt = ft_strdup(add);
		add = f_freenull(add);
		temp = f_freenull(temp);
	}
	else
		f_addback_node(&ms->list, f_new_node(temp));
}

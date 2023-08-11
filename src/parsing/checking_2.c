/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 07:41:15 by rofontai          #+#    #+#             */
/*   Updated: 2023/08/11 13:54:42 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	f_check_double_quote(t_meta *ms)
{
	int		start;
	char	*temp;

	start = ms->i++;
	while (ms->line[ms->i] && ms->line[ms->i] != 34)
		ms->i++;
	temp = ft_substr(ms->line, start, (ms->i - start) + 1);
	temp = f_pars_double_quote(ms, temp);
	if (temp == NULL)
	{
		ms->i++;
		return ;
	}
	f_addback_node(&ms->list, f_new_node(temp));
	ms->i++;
}

void	f_check_redir_left(t_meta *ms)
{
	int		start;
	int		end;
	char	*temp;

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 60)
		ms->i++;
	end = ms->i;
	if (end - start > 2)
	{
		ms->exit_status = 2;
		ms->error_flag = ms->exit_status;
		return ;
	}
	temp = ft_substr(ms->line, start, (end - start));
	f_addback_node(&ms->list, f_new_node(temp));
}

void	f_check_redir_right(t_meta *ms)
{
	int		start;
	int		end;
	char	*temp;

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 62)
		ms->i++;
	end = ms->i;
	if (end - start > 2)
	{
		ms->exit_status = 2;
		ms->error_flag = ms->exit_status;
		return ;
	}
	temp = ft_substr(ms->line, start, (end - start));
	f_addback_node(&ms->list, f_new_node(temp));
}

void	f_check_pipes(t_meta *ms)
{
	int		start;
	int		end;
	char	*temp;

	if (ms->i == 0)
	{
		ms->exit_status = 2;
		ms->error_flag = ms->exit_status;
		ms->i++;
		return ;
	}
	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 124)
		ms->i++;
	end = ms->i;
	if (end - start > 1)
	{
		ms->exit_status = 2;
		ms->error_flag = ms->exit_status;
		return ;
	}
	temp = ft_substr(ms->line, start, (end - start));
	f_addback_node(&ms->list, f_new_node(temp));
}

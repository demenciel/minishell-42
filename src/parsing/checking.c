/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:16:36 by rofontai          #+#    #+#             */
/*   Updated: 2023/08/11 07:19:39 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*f_pars_new_dollar(t_meta *ms, char *txt)
{
	char	*temp;
	char	*env;
	char	*prov;
	int		i;
	int		start;

	(void)ms;
	temp = ft_strdup(txt);
	txt = f_freenull(txt);
	i = 0;
	while (temp[i])
	{
		start = i;
		while (temp[i] && temp[i] != 36)
			i++;
		if (txt == NULL)
		{
			txt = ft_substr(temp, start, (i - start));
		}
		else
		{
			env = ft_substr(temp, start, (i - start));
			prov = ft_strjoin(txt, env);
			env = f_freenull(env);
			txt = f_freenull(txt);
			txt = ft_strdup(prov);
			prov = f_freenull(prov);
		}
		if (temp[i] && temp[i] == 36)
		{
			start = i++;
			while (temp[i] && f_check_env(temp[i]) == 1)
				i++;
			env = ft_substr(temp, start, (i - start));
			env = f_pars_dollar(ms, env);
			if (env)
			{
				prov = ft_strjoin(txt, env);
				env = f_freenull(env);
				txt = f_freenull(txt);
				txt = ft_strdup(prov);
				prov = f_freenull(prov);
			}
		}
	}
	temp = f_freenull(temp);
	return (txt);
}


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

char	*f_pars_double_quote(t_meta *ms, char *txt)
{
	char	*temp;
	char	*env;
	char	*prov;
	int		i;
	int		start;

	if (f_som_quote_double(txt) != 2)
	{
		ms->exit_status = 2;
		txt = f_freenull(txt);
		return (NULL);
	}
	temp = f_trimstr(txt, 34);
	txt = f_freenull(txt);
	i = 0;
	while (temp[i])
	{
		start = i;
		while (temp[i] && temp[i] != 36)
			i++;
		if (txt == NULL)
			txt = ft_substr(temp, start, (i - start));
		else
		{
			prov = ft_strjoin(txt, ft_substr(temp, start, (i - start)));
			txt = f_freenull(txt);
			txt = prov;
		}
		if (temp[i] && temp[i] == 36)
		{
			start = i++;
			while (temp[i] && f_check_env(temp[i]) == 1)
				i++;
			env = ft_substr(temp, start, (i - start));
			env = f_pars_dollar(ms, env);
			if (env)
			{
				prov = ft_strjoin(txt, env);
				txt = f_freenull(txt);
				txt = prov;
				env = f_freenull(env);
			}
		}
	}
	temp = f_freenull(temp);
	return (txt);
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

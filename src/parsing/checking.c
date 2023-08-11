/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:16:36 by rofontai          #+#    #+#             */
/*   Updated: 2023/08/11 14:03:10 by rofontai         ###   ########.fr       */
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

int f_check_quote_double_ok(t_meta *ms, char *txt)
{
	if (f_som_quote_double(txt) != 2)
	{
		ms->exit_status = 2;
		ms->error_flag = 1;
		txt = f_freenull(txt);
		return (-1);
	}
	return (0);
}


char	*f_pars_double_quote(t_meta *ms, char *txt)
{
	char	*temp;
	char	*prov;
	if (f_check_quote_double_ok(ms, txt) == -1)
		return (NULL);
	temp = f_trimstr(txt, 34);
	txt = f_freenull(txt);
	prov = f_copy(temp, ms);
	temp = f_freenull(temp);

	return (prov);
}

char *f_copy(char *temp, t_meta *ms)
{
	int start;
	char *prov;
	char *txt;
	int i;

	i = 0;
	txt = NULL;
	while (temp[i])
	{
		start = i;
		while (temp[i] && temp[i] != 36)
			i++;
		if (txt == NULL)
			txt = ft_substr(temp, start, (i - start));
		else
		{
			prov = ft_substr(temp, start, (i - start));
			txt = ft_strjoin(txt, prov);
			prov = f_freenull(prov);
		}
		if (temp[i] && temp[i] == 36)
			txt = f_copy_doll(&i, temp, txt, ms);
	}
	return (txt);
}

char *f_copy_doll(int *i, char *temp, char *txt, t_meta *ms)
{
	char *env;
	int start;
	char *prov;

	prov = NULL;
	start = *i;
	*i += 1;
	while (temp[*i] && f_check_env(temp[*i]) == 1)
		*i += 1;
	env = ft_substr(temp, start, (*i - start));
	env = f_pars_dollar(ms, env);
	if (env)
	{
		prov = ft_strjoin(txt, env);
		env = f_freenull(env);
		txt = f_freenull(txt);
	}
	return (prov);
}

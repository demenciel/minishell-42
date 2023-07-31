
#include "../../inc/minishell.h"

void	f_check_word(t_meta *ms)
{
	int	start;
	char *temp;

	if (DEBUG == 1)
		printf("" GRE "---f_check_word in---\n" WHT ""); // TODO Supprimer

	start = ms->i;
	while (ms->line[ms->i] && f_check_metachar(ms->line[ms->i]) == 0)
		ms->i++;
	temp = ft_substr(ms->line, start, (ms->i - start));
	if (temp == NULL)
		return ;
	f_addback_node(&ms->list, f_new_node(temp));

	if (DEBUG == 1)
		printf("" RED "---f_check_word_ out---\n" WHT ""); // TODO Supprimer
}

void	f_check_single_quote(t_meta *ms)
{
	int		start;
	char	*temp;

	if (DEBUG == 1)
		printf("" GRE "---f_check_single_quote in---\n" WHT ""); // TODO Supprimer

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

	if (DEBUG == 1)
		printf("" RED "---f_check_single_quote out---\n" WHT ""); // TODO Supprimer
}

char	*f_pars_simple_quote(t_meta *ms, char *txt)
{
	char	*temp;
	(void)ms;

	if (DEBUG == 1)
		printf("" GRE "---f_pars_simple_quote in---\n" WHT ""); // TODO Supprimer

	if (f_som_quote_simple(txt) != 2)
	{
		ms->exit_status = 5;
		f_freenull(txt);
		return (NULL);
	}
	temp = f_trimstr(txt, 39);
	f_freenull(txt);
	return (temp);

	if (DEBUG == 1)
		printf("" RED "---f_pars_simple_quote out---\n" WHT ""); // TODO Supprimer
}

void	f_check_dollar(t_meta *ms)
{
	int		start;
	char	*temp;

	if (DEBUG == 1)
		printf("" GRE "---f_check_dollar in---\n" WHT ""); // TODO Supprimer

	start = ms->i++;
	while (f_check_env(ms->line[ms->i]) == 1)
		ms->i++;
	temp = ft_substr(ms->line, start, (ms->i - start));
	temp = f_pars_dollar(ms, temp);
	if (temp == NULL)
		return ;
	f_addback_node(&ms->list, f_new_node(temp));

	if (DEBUG == 1)
		printf("" RED "---f_check_dollar out---\n" WHT ""); // TODO Supprimer
}

void f_new_check_dollar(t_meta *ms)
{
	int		start;
	char	*temp;

	if (DEBUG == 1)
		printf("" GRE "---f_new_check_dollar in---\n" WHT ""); // TODO Supprimer

	start = ms->i++;
	while (ms->line[ms->i] && f_check_env_dol(ms->line[ms->i]) == 1)
		ms->i++;
	temp = ft_substr(ms->line, start, (ms->i - start));
	temp = f_pars_new_dollar(ms, temp);
	if (temp == NULL)
		return ;
	f_addback_node(&ms->list, f_new_node(temp));

	if (DEBUG == 1)
		printf("" RED "---f_new_check_dollar out---\n" WHT ""); // TODO Supprimer
}

			// printf("env =%s=\n", env);
char	*f_pars_new_dollar(t_meta *ms, char *txt)
{
	char	*temp;
	char	*env;
	char *prov;
	int i;
	int start;
	(void)ms;

	if (DEBUG == 1)
		printf("" GRE "---f_pars_new_dollar in---\n" WHT ""); // TODO Supprimer
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
			txt = prov;
		}
		if (temp [i] && temp[i] == 36)
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
				txt = prov;
			}
		}
	}
	temp = f_freenull(temp);
	return (txt);

	if (DEBUG == 1)
		printf("" RED "---f_pars_new_dollar out---\n" WHT ""); // TODO Supprimer
}


char	*f_pars_dollar(t_meta *ms, char *txt)
{
	char	*temp;
	char	*env;
	char	*prov;
	int		nb;

	nb = ms->exit_status;
	if (DEBUG == 1)
		printf("" GRE "---f_pars_dollar in---\n" WHT ""); // TODO Supprimer

	if (ft_strlen(txt) == 1)
		return (txt);
	else if (txt[1] == '?')
	{
		txt = f_freenull(txt);
		return (ft_itoa(nb));
	}
	temp = f_trimstr(txt, 36);
	txt = f_freenull(txt);
	env = get_env(temp);
	temp = f_freenull(temp);
	if (env == NULL)
		return (NULL);
	else
	{
		prov = ft_strdup(env);
		env = f_freenull(env);
		return (prov);
	}

	if (DEBUG == 1)
		printf("" RED "---f_pars_dollar out---\n" WHT ""); // TODO Supprimer
}

void	f_check_double_quote(t_meta *ms)
{
	int		start;
	char	*temp;

	if (DEBUG == 1)
		printf("" GRE "---f_check_double_quote in---\n" WHT ""); // TODO Supprimer

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

	if (DEBUG == 1)
		printf("" RED "---f_check_double_quote out---\n" WHT ""); // TODO Supprimer
}

char	*f_pars_double_quote(t_meta *ms, char *txt) //TODO a travailer
{
	char	*temp;
	char	*env;
	char *prov;
	int i;
	int start;
	(void)ms;

	if (DEBUG == 1)
		printf("" GRE "---f_pars_double_quote in---\n" WHT ""); // TODO Supprimer
;
	if (f_som_quote_double(txt) != 2)
	{
		ms->exit_status = 6;
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
		if (temp [i] && temp[i] == 36)
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

	if (DEBUG == 1)
		printf("" RED "---f_pars_double_quote out---\n" WHT ""); // TODO Supprimer
}

void	f_check_redir_left(t_meta *ms)
{
	int	start;
	int	end;
	char *temp;

	if (DEBUG == 1)
		printf("" GRE "---f_check_redir_left in---\n" WHT ""); // TODO Supprimer

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 60)
		ms->i++;
	end = ms->i;
	if (end - start > 2)
	{
		ms->exit_status = 4;
		return ;
	}
	temp = ft_substr(ms->line, start, (end - start));
	f_addback_node(&ms->list, f_new_node(temp));

	if (DEBUG == 1)
		printf("" RED "---f_check_redir_left out---\n" WHT ""); // TODO Supprimer
}

void	f_check_redir_right(t_meta *ms)
{
	int	start;
	int	end;
	char *temp;
	if (DEBUG == 1)
		printf("" GRE "---f_check_redir_right in---\n" WHT ""); // TODO Supprimer

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 62)
		ms->i++;
	end = ms->i;
	if (end - start > 2)
	{
		ms->exit_status = 3;
		return ;
	}
	temp = ft_substr(ms->line, start, (end - start));
	f_addback_node(&ms->list, f_new_node(temp));

	if (DEBUG == 1)
		printf("" RED "---f_check_redir_right out---\n" WHT ""); // TODO Supprimer
}

void	f_check_pipes(t_meta *ms)
{
	int	start;
	int	end;
	char *temp;

	if (DEBUG == 1)
		printf("" GRE "---f_check_pipes in---\n" WHT ""); // TODO Supprimer

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

	if (DEBUG == 1)
		printf("" RED "---f_check_pipes out---\n" WHT ""); // TODO Supprimer
}


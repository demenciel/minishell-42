
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
		return ;
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
	temp = f_pars_dollar(temp);
	if (temp == NULL)
		return ;
	f_addback_node(&ms->list, f_new_node(temp));

	if (DEBUG == 1)
		printf("" RED "---f_check_dollar out---\n" WHT ""); // TODO Supprimer
}

char	*f_pars_dollar(char *txt)
{
	char	*temp;
	char	*env;

	if (DEBUG == 1)
		printf("" GRE "---f_pars_dollar in---\n" WHT ""); // TODO Supprimer

	if (ft_strlen(txt) == 1)
		return (txt);
	else if (txt[1] == '?')
		return (ft_itoa(1));
	temp = f_trimstr(txt, 36);
	txt = f_freenull(txt);
	env = getenv(temp);
	temp = f_freenull(temp);
	if (env == NULL)
		return (NULL);
	else
		return (ft_strdup(env));

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
		return ;
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
			env = f_pars_dollar(env);
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
		return ;
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
		return ;
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

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 124)
		ms->i++;
	end = ms->i;
	if (end - start > 1)
		return ;
	temp = ft_substr(ms->line, start, (end - start));
	f_addback_node(&ms->list, f_new_node(temp));
	if (DEBUG == 1)
		printf("" RED "---f_check_pipes out---\n" WHT ""); // TODO Supprimer
}

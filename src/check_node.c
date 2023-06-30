
#include "../inc/minishell.h"

void	f_pars_list(t_meta *ms)
{
	t_pars	*temp;

	printf("" GRE "---f_pars_list in---\n" WHT ""); // TODO Supprimer
	temp = ms->list;
	while (ms->list)
	{
		if (ms->list->txt[0] == 36)
			ms->list->txt = f_pars_dollar(ms->list->txt);
		else if (ms->list->txt[0] == 124 && ft_strlen(ms->list->txt) > 1)
			f_all_clean(ms, "Erreur de pipes");
		else if (ms->list->txt[0] == 62)
			f_pars_redir_right(ms);
		else if (ms->list->txt[0] == 60)
			f_pars_redir_left(ms);
		else if (ms->list->txt[0] == 39)
			f_pars_simple_quote(ms);
		else if (ms->list->txt[0] == 34)
			f_pars_double_quote(ms);
		else
			ms->list = ms->list->next;
	}
	ms->list = temp;
	printf("" RED "---f_pars_list out---\n" WHT ""); // TODO Supprimer
}

char	*f_pars_dollar(char *txt)
{
	char	*temp;

	printf("" GRE "---f_pars_dollar in---\n" WHT ""); // TODO Supprimer
	txt = ft_strtrim(txt, "$");
	temp = getenv(txt);
	if (temp == NULL)
		txt = "env doesn't";
	else
		txt = ft_strdup(temp);
	printf("" RED "---f_pars_dollar out---\n" WHT ""); // TODO Supprimer
	return (txt);
}

void	f_pars_redir_right(t_meta *ms)
{
	printf("" GRE "---f_pars_redir_right in---\n" WHT ""); // TODO Supprimer
	if (ft_strlen(ms->list->txt) == 1)
	{
		printf("1 redir right\n");
		ms->list = ms->list->next;
	}
	else if (ft_strlen(ms->list->txt) == 2)
	{
		printf("2 redir right\n");
		ms->list = ms->list->next;
	}
	else if (ft_strlen(ms->list->txt) > 2)
		f_all_clean(ms, "Erreur de >\n");
	printf("" RED "---f_pars_redir_right out---\n" WHT ""); // TODO Supprimer
}

void	f_pars_redir_left(t_meta *ms)
{
	printf("" GRE "---f_pars_redir_left in---\n" WHT ""); // TODO Supprimer
	if (ft_strlen(ms->list->txt) == 1)
	{
		printf("1 redir left\n");
		ms->list = ms->list->next;
	}
	else if (ft_strlen(ms->list->txt) == 2)
	{
		printf("2 redir left\n");
		ms->list = ms->list->next;
	}
	else if (ft_strlen(ms->list->txt) > 2)
		f_all_clean(ms, "Erreur de <\n");
	printf("" RED "---f_pars_redir_left out---\n" WHT ""); // TODO Supprimer
}

void	f_pars_simple_quote(t_meta *ms)
{
	printf("" GRE "---f_pars_simple_quote in---\n" WHT ""); // TODO Supprimer
	if (f_som_quote_simple(ms->list->txt) != 2)
		f_all_clean(ms, "erreur de quotes double");
	ms->list->txt = f_trimstr(ms->list->txt, 39);
	ms->list = ms->list->next;
	printf("" RED "---f_pars_simple_quote out---\n" WHT ""); // TODO Supprimer
}

void	f_pars_double_quote(t_meta *ms)
{
	int		i;
	char	*temp;
	char	*env;
	int		start;

	printf("" GRE "---f_pars_double_quote in---\n" WHT ""); // TODO Supprimer
	i = 0;
	temp = NULL;
	if (f_som_quote_double(ms->list->txt) != 2)
		f_all_clean(ms, "erreur de quotes double");
	ms->list->txt = f_trimstr(ms->list->txt, 34);
	while (ms->list->txt[i])
	{
		start = i;
		while (ms->list->txt[i] != 36 && ms->list->txt[i])
			i++;
		if (!temp)
			temp = ft_substr(ms->list->txt, start, i - start);
		else
			temp = ft_strjoin(temp, ft_substr(ms->list->txt, start, i - start));
		start = i;
		if (ms->list->txt[i] == 36)
		{
			while (ms->list->txt[i] > 32 && ms->list->txt[i] != 39
				&& ms->list->txt[i])
				i++;
			env = ft_substr(ms->list->txt, start, i - start);
			env = f_pars_dollar(env);
			printf("env =%s=\n", env);
			temp = ft_strjoin(temp, env);
		}
	}
	ms->list->txt = ft_strdup(temp);
	ms->list = ms->list->next;
	printf("" RED "---f_pars_double_quote out---\n" WHT ""); // TODO Supprimer
}

int	f_som_quote_double(char *txt)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (txt[i])
	{
		if (txt[i] == 34)
			flag++;
		i++;
	}
	return (flag);
}

int	f_som_quote_simple(char *txt)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (txt[i])
	{
		if (txt[i] == 39)
			flag++;
		i++;
	}
	return (flag);
}
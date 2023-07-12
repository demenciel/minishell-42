
#include "../inc/minishell.h"

int	f_som_quote_simple(char *txt)
{
	int	i;
	int	flag;

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

char	*f_pars_simple_quote(t_meta *ms, char *txt)
{
	char	*temp;

	printf("" GRE "---f_pars_simple_quote in---\n" WHT ""); // TODO Supprimer
	if (f_som_quote_simple(txt) != 2)
		f_all_clean(ms, "erreur de quotes double");
	temp = f_trimstr(txt, 39);
	free(txt);
	txt = NULL;
	return (temp);
	printf("" RED "---f_pars_simple_quote out---\n" WHT ""); // TODO Supprimer
}

char	*f_pars_dollar(char *txt)
{
	char	*temp;
	char	*env;

	printf("" GRE "---f_pars_dollar in---\n" WHT ""); // TODO Supprimer
	if (ft_strlen(txt) == 1)
		return (txt);
	else if (txt[1] == '?')
		return (ft_itoa(1));
	temp = f_trimstr(txt, 36);
	free(txt);
	env = getenv(temp);
	free(temp);
	if (env == NULL)
		txt = ft_strdup("env doesn't");
	else
		txt = ft_strdup(env);
	printf("" RED "---f_pars_dollar out---\n" WHT ""); // TODO Supprimer
	return (txt);
}

char	*f_pars_double_quote(t_meta *ms, char *txt)
{
	int		i;
	int		start;
	int		end;
	char	*temp;
	char	*env;
	// char	*test;

	i = 0;
	printf("" GRE "---f_pars_double_quote in---\n" WHT ""); // TODO Supprimer
	if (f_som_quote_double(txt) != 2)
		f_all_clean(ms, "erreur de quotes double");
	temp = f_trimstr(txt, 34);
	free(txt);
	txt = NULL;
	while (temp[i])
	{
		start = i;
		while (temp[i] != 36 && temp[i])
			i++;
		if (!txt)
			txt = ft_substr(temp, start, i - start);
		else
			txt = ft_strjoin(txt, ft_substr(temp, start, i - start));
		if (temp [i] && temp[i] == 36 && (temp[i + 1] != 0 || temp[i + 1] > 32))
		{
			start = i;
			while (temp[i] > 32 && temp[i + 1] != 36 && temp[i]
				&& temp[i] != 39)
				i++;
			if (temp[i] && temp[i + 1] == 36 && temp[i] > 32 && temp[i] != 124
				&& temp[i] != 62 && temp[i] != 60 && temp[i] != 34
				&& temp[i] != 39)
				end = i++;
			end = i;
			env = ft_substr(temp, start, end - start);
			env = f_pars_dollar(env);
			txt = ft_strjoin(txt, env);
			free(env);
			env = NULL;
		}
	}
	free(temp);
	return (txt);
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
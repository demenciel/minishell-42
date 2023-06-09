
#include "../../inc/minishell.h"

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

	if (f_som_quote_simple(txt) != 2)
		f_all_clean(ms, "erreur de quotes double");
	temp = f_trimstr(txt, 39);
	free(txt);
	txt = NULL;
	return (temp);
}

char	*f_pars_dollar(char *txt)
{
	char	*temp;
	char	*env;

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
	return (txt);
}

char	*f_pars_double_quote(t_meta *ms, char *txt)
{
	int		i;
	int		start;
	int		end;
	char	*temp;
	char	*env;

	i = 0;
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
		if (temp [i] && temp[i] == 36)
		{
			start = i++;
			while (f_check_env(temp[i]) == 1)
				i++;
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

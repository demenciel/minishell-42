
#include "../../inc/minishell.h"

t_pars	*f_new_node(char *str)
{
	t_pars	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(t_pars), 1);
	if (!new)
		return (NULL);
	new->txt = str;
	new->next = NULL;
	return (new);
}

t_pars	*f_last_node(t_pars *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	f_addback_node(t_pars **cmd, t_pars *new)
{
	t_pars	*last;

	if (!cmd || !new)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	last = f_last_node(*cmd);
	last->next = new;
}

int	f_check_metachar(char c)
{
	if (c == 124 || c == 62 || c == 60 || c == 39 || c == 34 || c == 36 || c <= 32)
		return (1);
	else
		return (0);
}

char	*f_trimstr(char *s1, char c)
{
	size_t	i;
	size_t	len_s1;
	char	*dest;

	i = 0;
	len_s1 = ft_strlen(s1);
	if (!len_s1)
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(&c, s1[i]))
		i++;
	while (s1[len_s1 - 1] && ft_strchr(&c, s1[len_s1 - 1]) && len_s1 > i)
		len_s1--;
	dest = ft_calloc(sizeof(char), (len_s1 - i) + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s1[i], (len_s1 - i) + 1);
	return (dest);
}

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

int	f_check_env(char c)
{
	if (ft_isalnum(c) == 1 || c == '_' || c == '?')
		return (1);
	else
		return (0);
}

int	f_check_env_dol(char c)
{
	if (ft_isalnum(c) == 1 || c == '_' || c == '?'|| c == '$' || c == 32)
		return (1);
	else
		return (0);
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

char	*f_join_char(const char *s1, const char s2)
{
	char			*join_str;
	unsigned int	i;

	i = 0;
	join_str = ft_calloc((ft_strlen(s1) + 2), sizeof(char));
	if (!join_str)
		return (NULL);
	while (s1[i])
	{
		join_str[i] = s1[i];
		i++;
	}
	join_str[i] = s2;
	return (join_str);
}

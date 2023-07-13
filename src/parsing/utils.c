
#include "../../inc/minishell.h"

t_meta	*f_init_meta(void)
{
	static t_meta	*new;

	if (!new)
	{
		new = ft_calloc(sizeof(t_meta), 1);
		if (!new)
			exit(EXIT_FAILURE);
		new->list = NULL;
		new->com_temp = NULL;
		new->in = NULL;
		new->out = NULL;
		new->i = 0;
		new->line = NULL;
		new->comand = NULL;
	}
	return (new);
}

void	f_all_clean(t_meta *ms, char *msg)
{
	if (ms->line)
		free(ms->line);
	if (ms->comand)
		f_free_comand(&ms->comand);
	if (ms->com_temp)
		free(ms->com_temp);
	if (ms->in)
		free(ms->in);
	if (ms->out)
		free(ms->out);
	if (ms->list)
		f_free_list(&ms->list);
	free(ms);
	if (msg)
	{
		printf("🚨 %s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	f_zero_list(t_meta *ms)
{
	if (ms->list)
	{
		f_free_list(&ms->list);
		ms->list = NULL;
	}
	if (ms->comand)
	{
		f_free_comand(&ms->comand);
		ms->comand = NULL;
	}
	if (ms->com_temp)
	{
		free(ms->com_temp);
		ms->com_temp = NULL;
	}
	if (ms->in)
	{
		free(ms->in);
		ms->in = NULL;
	}if (ms->out)
	{
		free(ms->out);
		ms->out = NULL;
	}
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
		return (0);
	ft_strlcpy(dest, &s1[i], (len_s1 - i) + 1);
	return (dest);
}
void	f_free_comand(t_comand **list)
{
	t_comand	*temp;

	if (!*list || !list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->stin);
		free((*list)->stout);
		ft_free_tab_char((*list)->com);
		free(*list);
		(*list) = temp;
	}
	*list = NULL;
}

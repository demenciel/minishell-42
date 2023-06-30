
#include "../inc/minishell.h"

void	f_zero_list(t_meta *ms)
{
	if (ms->list)
	{
		free(ms->list);
		ms->list = NULL;
	}
}

t_meta	*f_init_meta(void)
{
	static t_meta	*new;

	if (!new)
	{
		new = ft_calloc(sizeof(t_meta), 1);
		if (!new)
			return (NULL);
		new->list = NULL;
		new->i = 0;
		new->line = NULL;
	}
	return (new);
}

void	f_all_clean(t_meta *ms, char *msg)
{
	if (ms->line)
		free(ms->line);
	if (ms->list)
		f_free_list(&ms->list);
	f_free_meta(&ms);
	if (msg)
	{
		printf("🚨 %s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

char	*f_trimstr(char *s1, char c)
{
	size_t i;
	size_t len_s1;
	char *dest;

	i = 0;
	len_s1 = ft_strlen(s1);
	if (!len_s1)
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(&c, s1[i]))
		i++;
	while (s1[len_s1 - 1] && ft_strchr(&c, s1[len_s1 - 1]) && len_s1 > i)
		len_s1--;
	dest = ft_calloc(sizeof(char), (len_s1 - i));
	if (!dest)
		return (0);
	ft_strlcpy(dest, &s1[i], (len_s1 - i) + 1);
	return (dest);
}
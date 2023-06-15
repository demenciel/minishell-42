
#include "../../inc/minishell.h"

void f_zero_list(t_meta *ms)
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

void f_all_clean(t_meta *ms, char *msg)
{
	if (ms->line)
		free(ms->line);
	if (ms->list)
		f_free_list(&ms->list);
	f_free_meta(&ms);
	if (msg)
	{
		printf("🚨 %s\n", msg);
		exit (EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
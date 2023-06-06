
#include "../inc/minishell.h"

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
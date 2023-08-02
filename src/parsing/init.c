#include "../../inc/minishell.h"

t_meta	*f_init_meta(void)
{
	static t_meta	*new;

	if (!new)
	{
		new = ft_calloc(sizeof(t_meta), 1);
		if (!new)
			return (NULL);
		new->list = NULL;
		new->com_temp = NULL;
		new->in = NULL;
		new->out = NULL;
		new->i = 0;
		new->line = NULL;
		new->comand = NULL;
		new->exit_status = 0;
	}
	return (new);
}

#include "../../inc/minishell.h"

void	f_free_list(t_pars **list)
{
	t_pars	*temp;

	if (!*list || !list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->txt);
		free(*list);
		(*list) = temp;
	}
	*list = NULL;
}

t_pars	*f_new_node(char *str)
{
	t_pars	*new;

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
	while (list->next != NULL)
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

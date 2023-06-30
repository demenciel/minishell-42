
#include "../inc/minishell.h"

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

void	f_print_lst(t_pars *lst)
{
	t_pars	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp)
	{
		printf("com %d =%s=\n", i, temp->txt);
		i++;
		temp = temp->next;
	}
}

void	f_free_list(t_pars **list)
{
	t_pars	*temp;

	if (!*list || !list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		(*list) = temp;
	}
	*list = NULL;
}

void	f_free_meta(t_meta **ms)
{
	if (!*ms || !ms)
		return ;
	free(*ms);
	ms = NULL;
}

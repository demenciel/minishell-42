
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

t_meta	*f_init_meta(void)
{
	static t_meta	*new;

	if (!new)
	{
		new = ft_calloc(sizeof(t_meta), 1);
		if (!new)
			return (NULL);
		new->lst_size = 0;
		new->list = NULL;
		new->line = NULL;
	}
	return (new);
}

void	f_print_lst(t_pars *lst)
{
	t_pars *temp;
	int i;

	temp = lst;
	i = 0;
	while(temp)
	{
		printf ("com %d =%s=\n", i, temp->txt);
		i++;
		temp = temp->next;
	}
}
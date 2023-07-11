
#include "../inc/minishell.h"

t_comand	*f_new_com(void)
{
	t_comand	*new;

	new = ft_calloc(sizeof(t_comand), 1);
	if (!new)
		return (NULL);
	new->com = NULL;
	new->stin = NULL;
	new->stout = NULL;
	return (new);
}

t_comand	*f_last_com(t_comand *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	f_addback_com(t_comand **cmd, t_comand *new)
{
	t_comand	*last;

	if (!cmd || !new)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	last = f_last_com(*cmd);
	last->next = new;
}
void	f_split_pipes(t_meta *ms)
{
	printf("" GRE "---f_split_pipes in---\n" WHT ""); // TODO Supprimer

	t_comand *temp;
	char *com;
	t_pars *ptr;

	ptr = ms->list;
	while (ptr->next)
	{
		temp = f_new_com();
		while (ptr->next && ptr->txt[0] != '|')
		{
			com = ft_strjoin(com, ptr->txt);
			ptr = ptr->next;
		}
		temp->stin = ft_strdup(com);
		free(com);
		f_addback_com(&ms->comand, temp);
		temp = NULL;
		ptr = ptr->next;
	}
	ms->list = ptr;
	printf("" GRE "---f_split_pipes out---\n" WHT ""); // TODO Supprimer
}

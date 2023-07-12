
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

	t_pars *temp;

	temp = ms->list;
	while (temp)
	{
		while (temp && temp->txt[0] != 124)
		{
			if (temp && temp->txt[0] == 62)
			{
				f_add_in(ms, temp->txt);
				temp = temp->next;
				f_add_in(ms, temp->txt);
				printf("in =%s=\n", ms->in);
			}
			else if (temp && temp->txt[0] == 60)
			{
				f_add_out(ms, temp->txt);
				temp = temp->next;
				f_add_out(ms, temp->txt);
				printf("out =%s=\n", ms->out);
			}
			else
			{
				f_add_com(ms, temp->txt);
				printf("com_temp =%s=\n", ms->com_temp);
			}
			temp = temp->next;
		}
		if (temp == NULL)
			break ;
		temp = temp->next;
	}
	printf("" GRE "---f_split_pipes out---\n" WHT ""); // TODO Supprimer
}

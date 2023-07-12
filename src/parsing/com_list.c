
#include "../../inc/minishell.h"

t_comand	*f_new_com(char *com, char *in, char *out)
{
	t_comand	*new;

	new = ft_calloc(sizeof(t_comand), 1);
	if (!new)
		return (NULL);
	new->com = ft_split(com, 9);
	new->stin = ft_strdup(in);
	new->stout = ft_strdup(out);
	return (new);
}

void	f_zero_new_com(t_meta *ms)
{
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
	// printf("" GRE "---f_split_pipes in---\n" WHT ""); // TODO Supprimer

	t_pars *temp;

	temp = ms->list;
	while (temp)
	{
		while (temp && temp->txt[0] != 124)
		{
			if (temp && temp->txt[0] == 62)
			{
				f_add_out(ms, temp->txt);
				temp = temp->next;
				f_add_out(ms, temp->txt);
				printf("in =%s=\n", ms->in);
			}
			else if (temp && temp->txt[0] == 60)
			{
				f_add_in(ms, temp->txt);
				temp = temp->next;
				f_add_in(ms, temp->txt);
				printf("out =%s=\n", ms->out);
			}
			else
			{
				f_add_com(ms, temp->txt);
				// printf("com_temp =%s=\n", ms->com_temp);
			}
			temp = temp->next;
		}
		f_addback_com(&ms->comand, f_new_com(ms->com_temp, ms->in, ms->out));
		f_zero_new_com(ms);
		if (temp == NULL)
			break ;
		temp = temp->next;
	}
	// printf("" GRE "---f_split_pipes out---\n" WHT ""); // TODO Supprimer
}

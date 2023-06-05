
#include "../inc/minishell.h"

void	f_split_line(t_meta *ms)
{
	char **temp;
	int i;

	i = 0;
	temp = ft_split(ms->line, 32);
	while (temp[i])
	{
		temp[i] = ft_strtrim(temp[i], " ");
		f_addback_node(&ms->list, f_new_node(temp[i]));
		i++;
	}
	free(temp);
}

void	f_print_lst(t_pars *lst)
{
	t_pars *temp;
	int i;

	temp = lst;
	i = 0;
	while(temp)
	{
		printf ("com %d = %s \n", i, temp->txt);
		i++;
		temp = temp->next;
	}
}

void f_zero_list(t_meta *ms)
{
	if (ms->list)
	{
		free(ms->list);
		ms->list = NULL;
	}
}

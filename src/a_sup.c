
#include "../inc/minishell.h"

void	f_print_lst(t_pars *lst)
{
	t_pars *temp;
	int i;

	temp = lst;
	i = 0;
	while (temp)
	{
		printf("com %d =%s=\n", i, temp->txt);
		i++;
		temp = temp->next;
	}
}
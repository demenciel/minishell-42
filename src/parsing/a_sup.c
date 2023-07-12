
#include "../../inc/minishell.h"

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

void	f_print_lst_final(t_comand *lst)
{
	// printf("" GRE "---f_print_lst_final in---\n" WHT ""); // TODO Supprimer
	t_comand	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp)
	{
		if (temp->com)
			f_print(temp->com);
		printf("in %d =%s=\n", i, temp->stin);
		printf("out %d =%s=\n", i, temp->stout);
		i++;
		printf("----------------------------------------\n");
		temp = temp->next;
	}
	// printf("" GRE "---f_print_lst_final out---\n" WHT ""); // TODO Supprimer
}
void	f_print(char **cou)
{
	int i;

	i = 0;
	while (cou[i])
	{
		printf("%s\n", cou[i]);
		i++;
	}
}

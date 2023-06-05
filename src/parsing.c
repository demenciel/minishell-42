
#include "../inc/minishell.h"

void f_check_arg(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		printf("Not need an argument\n");
		exit (EXIT_FAILURE);
	}
}


void	f_split_line(t_meta *ms)
{
	int i;
	int start; //pas initialiser
	int end; //pas initialiser

	i = 0;

	while (ms->line[i] <= 32)
		i++;
	start = i;
	while (ms->line[i])
	{
		while ( ms->line[i] >= 32 && ms->line[i] != 124 && ms->line[i] != 62 && ms->line[i] != 60 && ms->line[i] != 39 && ms->line[i] != 34)
			i++;
		end = i;
		f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start))));
		start = end;
		while (ms->line[i] > 32 && (ms->line[i] == 124 || ms->line[i] == 62 || ms->line[i] == 60 || ms->line[i] == 39 || ms->line[i] == 34))
		{
			i++;
		}
		end = i;
		// f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start))));
	}
}
#include "../../inc/minishell.h"

void	f_check_arg(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		printf("Not need an argument\n");
		exit(EXIT_FAILURE);
	}
}

void	f_check_line(t_meta *ms)
{
	if (DEBUG == 1)
		printf("" GRE "---f_check_line in---\n" WHT ""); // TODO Supprimer

	while (ms->line[ms->i])
	{
		while (ms->line[ms->i] && ms->line[ms->i] <= 32)
			ms->i++;
		if (ms->line[ms->i] && ms->line[ms->i] == 124)
			f_check_pipes(ms);
		else if (ms->line[ms->i] && ms->line[ms->i] == 62)
			f_check_redir_right(ms);
		else if (ms->line[ms->i] && ms->line[ms->i] == 60)
			f_check_redir_left(ms);
		else if (ms->line[ms->i] && ms->line[ms->i] == 39)
			f_check_single_quote(ms);
		else if (ms->line[ms->i] && (ms->line[ms->i] == 34))
			f_check_double_quote(ms);
		else if (ms->line[ms->i] && ms->line[ms->i] == 36)
			f_new_check_dollar(ms);
		else
			f_check_word(ms);
	}
	ms->i = 0;

	if (DEBUG == 1)
		printf("" RED "---f_check_line out---\n" WHT ""); // TODO Supprimer
}

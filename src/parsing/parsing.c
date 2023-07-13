
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
	while (ms->line[ms->i])
	{
		while (ms->line[ms->i] <= 32)
			ms->i++;
		if (ms->line[ms->i] == 124)
			f_check_pipes(ms);
		else if (ms->line[ms->i] == 62)
			f_check_redir_right(ms);
		else if (ms->line[ms->i] == 60)
			f_check_redir_left(ms);
		else if (ms->line[ms->i] == 39)
			f_check_single_quote(ms);
		else if (ms->line[ms->i] == 34)
			f_check_double_quote(ms);
		else if (ms->line[ms->i] == 36)
			f_check_dollar(ms);
		else
			f_check_word(ms);
	}
	ms->i = 0;
}

void	f_check_word(t_meta *ms)
{
	int	start;
	int	end;

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] > 32 && (ms->line[ms->i] != 124
			&& ms->line[ms->i] != 62 && ms->line[ms->i] != 36
			&& ms->line[ms->i] != 60 && ms->line[ms->i] != 39
			&& ms->line[ms->i] != 34))
		ms->i++;
	end = ms->i;
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end
					- start))));
}

void	f_check_dollar(t_meta *ms)
{
	int		start;
	int		end;
	char	*temp;

	start = ms->i++;
	while (f_check_env(ms->line[ms->i]) == 1)
		ms->i++;
	end = ms->i;
	temp = ft_substr(ms->line, start, (end - start));
	temp = f_pars_dollar(temp);
	f_addback_node(&ms->list, f_new_node(temp));
}

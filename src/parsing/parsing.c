
#include "../../inc/minishell.h"

void f_check_arg(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		printf("Not need an argument\n");
		exit (EXIT_FAILURE);
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


void	f_check_pipes(t_meta *ms)
{
	printf (""GRE"---f_check_pipes in---\n"WHT""); //TODO Supprimer
	int start;
	int end;

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 124)
		ms->i++;
	end = ms->i;
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start))));
	printf (""RED"---f_check_pipes out---\n"WHT""); //TODO Supprimer
}

void	f_check_redir_right(t_meta *ms)
{
	printf (""GRE"---f_check_redir_right in---\n"WHT""); //TODO Supprimer
	int start;
	int end;

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 62)
		ms->i++;
	end = ms->i;
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start))));
	printf (""RED"---f_check_redir_right out---\n"WHT""); //TODO Supprimer
}

void	f_check_redir_left(t_meta *ms)
{
	printf (""GRE"---f_check_redir_left in---\n"WHT""); //TODO Supprimer
	int start;
	int end;

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 60)
		ms->i++;
	end = ms->i;
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start))));
	printf (""RED"---f_check_redir_left out---\n"WHT""); //TODO Supprimer
}

void	f_check_single_quote(t_meta *ms)
{
	printf (""GRE"---f_check_single_quote in---\n"WHT""); //TODO Supprimer
	int start;
	int end;

	start = ms->i++;
	while (ms->line[ms->i] != 39 && ms->line[ms->i])
		ms->i++;
	end = ms->i++;
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start) + 1)));
	printf (""RED"---f_check_single_quote out---\n"WHT""); //TODO Supprimer
}

void	f_check_double_quote(t_meta *ms)
{
	printf (""GRE"---f_check_double_quote in---\n"WHT""); //TODO Supprimer
	int start;
	int end;

	start = ms->i++;
	while (ms->line[ms->i] != 34 && ms->line[ms->i])
		ms->i++;
	end = ms->i++;
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start) + 1)));
	printf (""RED"---f_check_double_quote out---\n"WHT""); //TODO Supprimer
}

void	f_check_word(t_meta *ms)
{
	printf (""GRE"---f_check_word in---\n"WHT""); //TODO Supprimer
	int start;
	int end;

	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] > 32 &&
	(ms->line[ms->i] != 124 && ms->line[ms->i] != 62 && ms->line[ms->i] != 36 &&
	ms->line[ms->i] != 60 && ms->line[ms->i] != 39 && ms->line[ms->i] != 34))
		ms->i++;
	end = ms->i;
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start))));
	printf (""RED"---f_check_word_ out---\n"WHT""); //TODO Supprimer
}

void	f_check_dollar(t_meta *ms)
{
	printf (""GRE"---f_check_dollar in---\n"WHT""); //TODO Supprimer
	int start;
	int end;

	start = ms->i;
	// printf ("i start = %d\n", ms->i); //TODO Supprimer
	while (ms->line[ms->i] && ms->line[ms->i] > 32 &&
	ms->line[ms->i] != 124 && ms->line[ms->i] != 62 &&ms->line[ms->i + 1] != 36 &&
	ms->line[ms->i] != 60 && ms->line[ms->i] != 39 && ms->line[ms->i] != 34)
		ms->i++;
	if (ms->line[ms->i + 1] == 36 && ms->line[ms->i] && ms->line[ms->i] > 32 &&
	ms->line[ms->i] != 124 && ms->line[ms->i] != 62 &&
	ms->line[ms->i] != 60 && ms->line[ms->i] != 39 && ms->line[ms->i] != 34)
		end = ms->i++;
	end = ms->i;
	// printf ("i end = %d\n", ms->i); //TODO Supprimer
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end - start))));
	printf (""RED"---f_check_dollar out---\n"WHT""); //TODO Supprimer
}

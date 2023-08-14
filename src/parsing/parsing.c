/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:53:08 by romain            #+#    #+#             */
/*   Updated: 2023/08/14 11:42:00 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

void	f_cut_add_out(t_meta *ms, t_pars **temp)
{
	f_add_out(ms, (*temp)->txt);
	if (*temp)
	{
		*temp = (*temp)->next;
		if (*temp && (*temp)->txt != NULL)
			f_add_out(ms, (*temp)->txt);
	}
}

void	f_cut_add_in(t_meta *ms, t_pars **temp)
{
	f_add_in(ms, (*temp)->txt);
	if (*temp)
	{
		*temp = (*temp)->next;
		if (*temp && (*temp)->txt != NULL)
			f_add_in(ms, (*temp)->txt);
	}
}

void	f_print_error(t_meta *ms)
{
	write(2, "minishell: ", 12);
	write (2, "syntax error near unexpected\n", 29);
	ms->exit_status = 2;
	ms->error_flag = 1;
}

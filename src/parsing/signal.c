/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:18:09 by romain            #+#    #+#             */
/*   Updated: 2023/08/14 11:36:33 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	f_sighandler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	f_sighandler_com(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	f_signals(void)
{
	signal(SIGQUIT, f_sighandler);
	signal(SIGINT, f_sighandler);
	signal(SIGQUIT, SIG_IGN);
}

void	f_signal_in(int status, t_meta *ms)
{
	if (WIFEXITED(status) && ms->error_flag == 0)
		ms->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			ms->exit_status = 130;
		else if (WTERMSIG(status) == 3)
		{
			ft_putstr_fd("Quit : 3\n", STDOUT_FILENO);
			ms->exit_status = 131;
		}
		else
			ms->exit_status = WTERMSIG(status);
	}
}

void	f_exit_syntax_error(t_meta *ms, int flag)
{
	if (ms->error_flag == 0)
		printf ("minishell: syntax error near unexpected token\n");
	ms->exit_status = flag;
	ms->error_flag = ms->exit_status;
}

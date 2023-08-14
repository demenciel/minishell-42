/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:32:03 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 18:57:59 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Checks if there are fd's with the command, if so redirects
 * 		the output or input to the correct fd
 * @param pipe The write end of the pipe
 * @param ms The principal structure with the nodes
 * @return The write end of the command
*/
int	redirect_nodes(int *pipe, t_meta *ms)
{
	int	out_fd;
	int	in_fd;

	in_fd = g()->in_fd;
	if (ms->comand->next == NULL)
		out_fd = 1;
	else
		out_fd = pipe[1];
	if (ms->comand->stin != NULL)
	{
		in_fd = redirect_in(ms, pipe);
		if (g()->in_fd < 0)
			return (FD_ERROR);
	}
	if (ms->comand->stout != NULL)
	{
		out_fd = redirect_out(ms);
		if (out_fd < 0)
			return (FD_ERROR);
		g()->redir_flag = true;
	}
	return (out_fd);
}

/**
 * @brief Loops readline and add each line to rl history until limiter is found
 * @param limiter The limiter for the heredocs
 */
int	heredocs(char *limiter, int input_fd)
{
	char	*rl_line;

	if (!limiter || *limiter == '\0')
		return (HEREDOC_ERROR);
	while (1)
	{
		rl_line = readline("heredoc > ");
		if (ft_strncmp(limiter, rl_line, (ft_strlen(limiter) + 1)) == 0)
		{
			free(rl_line);
			break ;
		}
		ft_putstr_fd(rl_line, input_fd);
		ft_putchar_fd('\n', input_fd);
		free(rl_line);
	}
	return (0);
}

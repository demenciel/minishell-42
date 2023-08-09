/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:40:16 by acouture          #+#    #+#             */
/*   Updated: 2023/08/09 13:41:04 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	redirect_nodes(int *pipe, t_comand *node)
{
	int	out_fd;

	if (node->next == NULL)
		out_fd = 1;
	else
		out_fd = pipe[1];
	if (node->stin != NULL)
	{
		g()->in_fd = redirect_in(node, pipe);
		if (g()->in_fd == FD_ERROR)
			return (FD_ERROR);
		else if (g()->in_fd == HEREDOC_ERROR)
			return (HEREDOC_ERROR);
	}
	if (node->stout != NULL)
	{
		out_fd = redirect_out(node);
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

int redirect_in(t_comand *node, int *pipe)
{
	char **fd;
	int in_fd;

	fd = ft_split(node->stin, 29);
	if (ft_strlen(fd[0]) == 2)
	{
		if (fd[1])
		{
			if (heredocs(fd[1], pipe[1]) < 0)
			{
				ft_2darr_free(fd);
				close(pipe[1]);
				return (HEREDOC_ERROR);
			}
			else
			{
				close(pipe[1]);
				return (pipe[0]);
			}
		}
	}
	else
	{
		in_fd = open_rd_fd(ft_strtrim(fd[1], "<"));
		if (in_fd < 0)
		{
			ft_2darr_free(fd);
			return (FD_ERROR);
		}
		ft_2darr_free(fd);
		return (in_fd);
	}
	return (0);
}

int redirect_out(t_comand *node)
{
	char **fd;
	int out_fd;

	fd = ft_split(node->stout, 29);
	if (ft_strlen(fd[0]) == 2)
	{
		out_fd = append_rd_fd(fd[1]);
		if (out_fd < 0)
		{
			ft_2darr_free(fd);
			return (FD_ERROR);
		}
		ft_2darr_free(fd);
		return (out_fd);
	}
	else
	{
		out_fd = create_rd_fd(fd[1]);
		if (out_fd < 0)
		{
			ft_2darr_free(fd);
			return (FD_ERROR);
		}
		ft_2darr_free(fd);
		return (out_fd);
	}
	return (0);
}
	
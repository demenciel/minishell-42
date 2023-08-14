/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:41:33 by acouture          #+#    #+#             */
/*   Updated: 2023/08/11 14:32:43 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Checks if the node contains the token for heredoc, and if so,
 *      executes the heredoc function, and returns the output of the heredoc
 * @param fd The token for heredoc
 * @param pipe The pipe to write into
 * @return The output fd
 */
int	heredoc_exec(char **fd, int *pipe, int i)
{
	if (i % 2 != 0)
	{
		if (heredocs(fd[i], pipe[1]) < 0)
		{
			close(pipe[1]);
			return (HEREDOC_ERROR);
		}
		else
		{
			close(pipe[1]);
			return (pipe[0]);
		}
	}
	return (0);
}

/**
 * @brief Checks if the token is a len of 2, if so,
	executes the heredoc function
 * 			and assigns its output to the return. If token is not len of 2,
 * 			open and reads the fd, then returns this new fd.
 * @param i The index of the list of fd
 * @param fd The list of fd
 * @param pipe The write end of the pipe
 * @return The fd for the redirection
 */
int	return_in_fd(t_meta *ms, int i, char **fd, int *pipe)
{
	int	in_fd;

	if (ft_strlen(fd[i]) == 2)
	{
		i++;
		in_fd = heredoc_exec(fd, pipe, i);
		if (in_fd == HEREDOC_ERROR)
			return (HEREDOC_ERROR);
	}
	else
	{
		i++;
		in_fd = open_rd_fd(ms, ft_strtrim(fd[i], "<"));
		if (in_fd < 0)
		{
			ft_2darr_free(fd);
			return (FD_ERROR);
		}
	}
	return (in_fd);
}

/**
 * @brief Splits the input fds accompanying the command node,
	redirects the input
 * 		of the node to the right fd
 * @param ms The main structure with the nodes
 * @param pipe The write end of the pipe
 * @return The input fd of the command
 */
int	redirect_in(t_meta *ms, int *pipe)
{
	int		in_fd;
	char	**fd;
	size_t	i;

	i = 0;
	fd = ft_split(ms->comand->stin, 29);
	while (i < ft_2darr_len(fd))
	{
		in_fd = return_in_fd(ms, i, fd, pipe);
		i++;
	}
	ft_2darr_free(fd);
	return (in_fd);
}

int	return_out_fd(t_meta *ms, char **fd, int i, int out_fd)
{
	if (ft_strlen(fd[i]) == 2)
	{
		i++;
		if (i % 2 != 0)
			out_fd = append_rd_fd(ms, fd[i]);
		if (out_fd < 0)
		{
			ft_2darr_free(fd);
			return (FD_ERROR);
		}
	}
	else
	{
		i++;
		if (i % 2 != 0)
			out_fd = create_rd_fd(ms, fd[i]);
		if (out_fd < 0)
		{
			ft_2darr_free(fd);
			return (FD_ERROR);
		}
	}
	return (out_fd);
}

int	redirect_out(t_meta *ms)
{
	char	**fd;
	int		out_fd;
	size_t	i;

	i = 0;
	out_fd = 1;
	fd = ft_split(ms->comand->stout, 29);
	while (i < ft_2darr_len(fd))
	{
		out_fd = return_out_fd(ms, fd, i, out_fd);
		i++;
	}
	ft_2darr_free(fd);
	return (out_fd);
}

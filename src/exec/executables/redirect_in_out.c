/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:41:33 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 18:27:33 by acouture         ###   ########.fr       */
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
	if (fd[i])
	{
		if (heredocs(fd[1], pipe[1]) < 0)
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

int	redirect_in(t_meta *ms, int *pipe)
{
	char	**fd;
	int		in_fd;
	size_t	i;

	i = 0;
	fd = ft_split(ms->comand->stin, 29);
	while (i < ft_2darr_len(fd))
	{
		if (ft_strlen(fd[i]) == 2)
		{
			i++;
			in_fd = heredoc_exec(fd, pipe, i);
		}
		else
		{
			i++;
			in_fd = open_rd_fd(ft_strtrim(fd[i], "<"));
			if (in_fd < 0)
			{
				ft_2darr_free(fd);
				return (FD_ERROR);
			}
		}
	}
	ft_2darr_free(fd);
	return (in_fd);
}

int	redirect_out(t_meta *ms)
{
	char	**fd;
	int		out_fd;
	size_t 	i;

	i = 0;
	out_fd = 1;
	fd = ft_split(ms->comand->stout, 29);
	while (i < ft_2darr_len(fd))
	{
		if (ft_strlen(fd[i]) == 2)
		{
			i++;
			if (i % 2 != 0)
				out_fd = append_rd_fd(fd[i]);
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
				out_fd = create_rd_fd(fd[i]);
			if (out_fd < 0)
			{
				ft_2darr_free(fd);
				return (FD_ERROR);
			}
		}
		i++;
	}
	ft_2darr_free(fd);
	return (out_fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:41:33 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 17:09:12 by rofontai         ###   ########.fr       */
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
int heredoc_exec(char **fd, int *pipe)
{
    if (fd[1])
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
    int     heredoc_return;

	fd = ft_split(ms->comand->stin, 29);
	if (ft_strlen(fd[0]) == 2)
	{
        heredoc_return = heredoc_exec(fd, pipe);
		ft_2darr_free(fd);
        return (heredoc_return);
	}
	else
	{
		in_fd = open_rd_fd(ms, ft_strtrim(fd[1], "<"));
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

int	redirect_out(t_meta *ms)
{
	char	**fd;
	int		out_fd;

	fd = ft_split(ms->comand->stout, 29);
	if (ft_strlen(fd[0]) == 2)
	{
		out_fd = append_rd_fd(ms, fd[1]);
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
		out_fd = create_rd_fd(ms, fd[1]);
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

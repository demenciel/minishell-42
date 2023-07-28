

#include "../../inc/minishell.h"

/**
 * @brief Loops readline and add each line to rl history until limiter is found
 * @param limiter The limiter for the heredocs
*/
int	heredocs(char *limiter)
{
	char	*rl_line;

	if (!limiter || *limiter == '\0')
		return (HEREDOC_ERROR);
	while (1)
	{
		rl_line = readline("heredoc > ");
		if (ft_strnstr(rl_line, limiter, ft_strlen(rl_line)))
			break ;
		free(rl_line);
	}
	return (0);
}

int redirect_in(t_comand *node)
{
	char **fd;
	int in_fd;

	fd = ft_split(node->stin, 29);
	if (ft_strlen(fd[0]) == 2)
	{
		if (fd[1])
		{
			if (heredocs(fd[1]) < 0)
				return (HEREDOC_ERROR);
		}
	}
	else
	{
		in_fd = open_rd_fd(fd[1]);
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

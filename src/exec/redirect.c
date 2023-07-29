

#include "../../inc/minishell.h"

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
		if (ft_strncmp(rl_line, limiter, ft_strlen(limiter)) == 0)
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

// void	exec_multi_node(t_comand *node)
// {
// 	int 	pipe_end[2];
// 	int 	out_fd;
// 	int 	nb_node;
// 	int i = 0;

// 	if (!node || node->com[0] == NULL)
// 		return ;
// 	nb_node = lst_size(node);
// 	g()->pid = malloc(sizeof(pid_t) * (nb_node + 1));
// 	while (node)
// 	{
// 		if (pipe(pipe_end) != 0)
// 			return ;
// 		g()->in_fd = pipe_end[0];
// 		out_fd = redirect_nodes(pipe_end, node);
// 		if (out_fd < 0)
// 			return ;
// 		else if (out_fd == HEREDOC_ERROR)
// 			break ;
// 		if (!ft_check_builtins(node->com))
// 		{
// 			g()->pid[i] = fork();
// 			if (g()->pid[i] == 0)
// 			{
// 				close(pipe_end[0]);
// 				dup2(g()->in_fd, STDIN_FILENO);
// 				close(g()->in_fd);
// 				dup2(out_fd, STDIN_FILENO);
// 				exec_cmd(node->com);
// 				f_exit(mt());
// 			}
// 			else
// 				close(pipe_end[1]);
// 			// pipex(node, true, g()->in_fd, out_fd);
// 		}
// 		else
// 		{
// 			find_builtins(node, out_fd);
// 			close(out_fd);
// 		}
// 		i++;
// 		node = node->next;
// 	}
	
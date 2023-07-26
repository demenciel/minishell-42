#include "../../inc/minishell.h"

/**
 * @brief Initialize the content of the exec struct
*/
void	init_exec_struct(void)
{
	t_exec	*p;

	p = g();
	p->in_fd = 0;
	p->old_fd = 0;
	p->out_fd = 0;
	p->env_list = NULL;
	p->export_list = NULL;
}

int	lst_size(t_comand *lst)
{
	int i;
	t_comand *node;
	i = 0;

	node = lst;
	if (!node || node->next == NULL)
		return (1);
	while (node->next)
	{
		i++;
		node = node->next;
	}
	if (node->next == NULL)
		i++;
	return (i);
}

int redirect_nodes(int pipe_write, t_comand *node)
{
	int out_fd;

	if (node->next == NULL)
		out_fd = 1;
	else
		out_fd = pipe_write;
	if (node->stin != NULL)
	{
		g()->in_fd = redirect_in(node);
		if (g()->in_fd == FD_ERROR)
			return (FD_ERROR);
		else if (g()->in_fd == -2)
			return (HEREDOC_ERROR);
	}
	if (node->stout != NULL)
	{
		out_fd = redirect_out(node);
		if (out_fd < 0)
			return (FD_ERROR);
	}
	return (out_fd);
}

/**
 * @brief Iterates over all the nodes in the program,
 * 			assigns the appropriate fd, and executes the node
 * @param node The node to be executed
*/
void	exec_multi_node(t_comand *node)
{
	int 	pipe_end[2];
	int 	out_fd;
	pid_t	*pid;
	int i = 0;

	if (pipe(pipe_end) != 0)
		return ;
	i = lst_size(node);
	pid = malloc(sizeof(pid_t) * (i + 1));
	i = 0;
	while (node)
	{
		g()->in_fd = pipe_end[0];
		out_fd = redirect_nodes(pipe_end[1], node);
		if (out_fd < 0)
			return ;
		else if (out_fd == HEREDOC_SUCCESS)
			break ;
		if (!ft_check_builtins(node->com))
		{
			pid[i] = fork();
			pipex(pid[i], node->com, pipe_end, g()->in_fd, out_fd);
			i++;
		}
		else
		{
			find_builtins(node, out_fd);
			close(out_fd);
		}
		printf("NODE %s\n", node->com[0]);
		printf("IN FD %d\n", g()->in_fd);
		printf("OUT FD %d\n", out_fd);
		node = node->next;
	}
	for (int j = 0; j < i; j++)
    {
        int status;
        waitpid(pid[j], &status, 0);
		close(g()->in_fd);
		close(pipe_end[0]);
		close(pipe_end[1]);
    }
}

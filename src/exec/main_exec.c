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
	p->pid = 0;
}

int	lst_size(t_comand *lst)
{
	int i;
	t_comand *node;
	i = 0;

	node = lst;
	if (!node)
		return (0);
	while (node->next)
	{
		i++;
		node = node->next;
	}
	if (node->next == NULL)
		i++;
	return (i);
}

int redirect_nodes(int *pipe, t_comand *node)
{
	int out_fd;

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
	}
	return (out_fd);
}

void	wait_free_pid(t_comand *node, int *pipe)
{
	int i;

	i = 0;
	(void)pipe;
	while (i <= lst_size(node))
	{
		waitpid(g()->pid[i], &mt()->exit_status, 0);
		close(g()->in_fd);
		for (int i = 3; i < 200; i++) {
			close(i);
		}
		i++;
	}
	free(g()->pid);
}

/**
 * @brief Executes a single node in the program
 * @param node The node to be executed
 * @param fd The fd into which to write the execution
*/
void	exec_one_node(t_comand *node, int fd, int out_fd)
{
	if (ft_check_builtins(node->com))
		find_builtins(node, out_fd);
	else
		pipex(node, false, fd, out_fd);
}

int	init_pid_and_nb_node(t_comand *node)
{
	int 	nb_node;
	int i;

	i = 0;
	nb_node = lst_size(node);
	g()->pid = malloc(sizeof(pid_t) * (nb_node));
	if (!g()->pid)
		f_all_clean_exit(mt(), MALLOC_ERROR);
	while (i < nb_node)
	{
		g()->pid[i] = -1;
		i++;
	}
	return (nb_node);
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
	int 	nb_node;

	if (!node || node->com[0] == NULL)
		return ;
	if (pipe(pipe_end) != 0)
		return ;
	nb_node = init_pid_and_nb_node(node);
	g()->in_fd = pipe_end[0];
	g()->pid = malloc(sizeof(pid_t) * (nb_node + 1));
	while (node)
	{
		out_fd = redirect_nodes(pipe_end, node);
		if (out_fd < 0)
			return ;
		else if (out_fd == HEREDOC_ERROR)
			break ;
		if (node->next == NULL)
			exec_one_node(node, g()->in_fd, out_fd);
		else
		{
			if (!ft_check_builtins(node->com))
				pipex(node, true, g()->in_fd, out_fd);
			else
			{
				find_builtins(node, out_fd);
				close(out_fd);
			}
		}
		node = node->next;
	}
	wait_free_pid(node, pipe_end);
}

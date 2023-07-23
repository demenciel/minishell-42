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
	p->out_fd = -1;
	p->env_list = NULL;
	p->export_list = NULL;
}

/**
 * @brief Executes a single node in the program
 * @param node The node to be executed
 * @param fd The fd into which to write the execution
*/
void	exec_one_node(t_comand *node, int fd)
{
	if (ft_check_builtins(node->com))
		find_builtins(node, fd);
	else
		pipex(node->com, false, fd);
}

/**
 * @brief Iterates over all the nodes in the program,
 * 			assigns the appropriate fd, and executes the node
 * @param node The node to be executed
*/
void	exec_multi_node(t_comand *node)
{
	int fd;

	while (node)
	{
		if (node->stin != NULL)
		{
			fd = open_rd_fd(node->stin);
			g()->in_fd = fd;
			close(fd);
		}
		if (node->next == NULL)
			exec_one_node(node, g()->in_fd);
		else if (!ft_check_builtins(node->com))
			pipex(node->com, true, g()->in_fd);
		else
			find_builtins(node, g()->in_fd);
		node = node->next;
	}
}

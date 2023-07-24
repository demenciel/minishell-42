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
		pipex(node->com, false, fd, out_fd);
}

/**
 * @brief Iterates over all the nodes in the program,
 * 			assigns the appropriate fd, and executes the node
 * @param node The node to be executed
*/
void	exec_multi_node(t_comand *node)
{
	int pipe_end[2];
	int out_fd;

	if (pipe(pipe_end) != 0)
		return ;
	g()->in_fd = pipe_end[0];
	g()->out_fd = pipe_end[1];
	while (node)
	{
		out_fd = 0;
		if (node->stin != NULL)
			g()->in_fd = open_rd_fd(node->stin);
		else if (node->stout != NULL)
		{
			char **res = ft_split(node->stout, 29);
			out_fd = create_rd_fd(res[1]);
		}
		if (node->next == NULL)
			exec_one_node(node, g()->in_fd, out_fd);
		else 
		{
			if (!ft_check_builtins(node->com))
			{
				pipex(node->com, true, g()->in_fd, out_fd);
			}
			else
			{
				find_builtins(node, g()->out_fd);
				// si il faut pipe, ecrit dans le fd write
				close(g()->out_fd);
			}
		}
		node = node->next;
	}
	close(g()->in_fd);
	close(g()->out_fd);
	close(pipe_end[0]);
	close(pipe_end[1]);
}

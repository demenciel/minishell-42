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
	if (node->next == NULL)
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

int redirect_nodes(bool single_node, int pipe_write, t_comand *node)
{
	int out_fd;

	if (!single_node)
		out_fd = pipe_write;
	if (single_node || node->next == NULL)
		out_fd = 1;
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
		if (out_fd < -1)
			return (FD_ERROR);
	}
	return (out_fd);
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
	if (DEBUG == 1 )
		printf("" GRE "---exec in---\n" WHT ""); // TODO Supprimer
	int 	pipe_end[2];
	int 	out_fd;
	bool	single_node;

	single_node = true;
	if (pipe(pipe_end) != 0)
		return ;
	g()->in_fd = pipe_end[0];
	if (lst_size(node) > 1)
		single_node = false;
	while (node)
	{
		out_fd = redirect_nodes(single_node, pipe_end[1], node);
		if (out_fd < 0)
			return ;
		else if (out_fd == HEREDOC_SUCCESS)
			break ;
		if (node->next == NULL)
			exec_one_node(node, g()->in_fd, out_fd);
		else
		{
			if (!ft_check_builtins(node->com))
				pipex(node->com, true, g()->in_fd, out_fd);
			else
			{
				find_builtins(node, out_fd);
				close(out_fd);
			}
		}
		node = node->next;
	}
	close(g()->in_fd);
	close(pipe_end[0]);
	close(pipe_end[1]);
	
	if (DEBUG == 1 )
		printf("" RED "---exec out---\n" WHT ""); // TODO Supprimer
}

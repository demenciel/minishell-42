#include "../../inc/minishell.h"

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

void	exec_one_node(t_comand *node, int fd)
{
	if (ft_check_builtins(node->com))
		find_builtins(node, fd);
	else
		pipex(node->com, false, fd);
}

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

/**
 * TRYING TO PASS PIPE ENDS TO THE FUNCTIONS SO EVEN BUILTINS
 * CAN WRITE INTO THE PIPE, SO THEN THE OTHER COMMAND CAN READ FROM
 * THAT PIPE
*/
#include "../../inc/minishell.h"

void	init_exec_struct(void)
{
	t_exec	*p;

	p = g();
	p->in_fd = open_rd_fd(NULL);
    p->old_fd = 0;
	p->out_fd = -1;
	p->env_list = NULL;
	p->export_list = NULL;
}

void exec_one_node(t_comand *node, int fd)
{
	if (ft_check_builtins(node->com))
        find_builtins(node, 0);
	else
    	pipex(node->com, false, fd);
}

void exec_multi_node(t_comand *node)
{
    int input_fd;

    while (node)
    {
        input_fd = 0;
        if (node->stin != NULL)
            g()->in_fd = open_rd_fd(node->stin);
        input_fd = g()->in_fd;
        if (node->next == NULL)
            exec_one_node(node, input_fd);
        if (ft_check_builtins(node->com))
            find_builtins(node, input_fd);
        else
            pipex(node->com, true, input_fd);
        
        node = node->next;
    }
}
#include "../inc/minishell.h"

// PARSING

t_exec	*g(void)
{
	static t_exec	data;

	return (&data);
}

void	init_exec_struct(void)
{
	t_exec	*p;

	p = g();
	p->in_fd = open_rd_fd(NULL);
	p->out_fd = -1;
	p->env_list = NULL;
	p->export_list = NULL;
}

void    ft_reset_exec()
{
    t_exec *exec;

    exec = g();
}

t_meta	*mt(void)
{
	static t_meta	data;

	return (&data);
}



/**
 * @brief Inits the environment, assigns it to env_list
 * @param env The computer environment
*/
void    init_env(char **env)
{
    int size;
    t_exec *exec;

    size = 0;
    exec = g();
    while (env[size])
        size++;
    exec->env_list = malloc(sizeof(char *) * (size + 1));
    if (!exec->env_list)
        return ;
    size = 0;
    while (env[size])
    {
        exec->env_list[size] = ft_strdup(env[size]);
        size++;
    }
    exec->env_list[size] = NULL;
}

void ft_print_details(t_meta *ms)
{
	printf("\n=%s=\n\n", ms->line);
		printf("\n");
		f_print_lst(ms->list);
		printf("\n");
		printf("\n");
		f_print_lst_final(ms->comand);
		// printf("com_temp =%s=", ms->com_temp);
		printf("\n");
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
        if (node->stin != NULL)
            input_fd = open_rd_fd(node->stin);
        else
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


int	main(int ac, char **av, char **env)
{
	t_meta *ms;
	t_comand *node;
    // int old_fd;

	f_check_arg(ac, av);
	ms = f_init_meta();
    init_exec_struct();
    init_env(env);
	while (1)
	{
		ms->line = readline("minishell > ");
		if (ft_strncmp(ms->line, "exit", 4) == 0)
			break ;
		f_check_line(ms);
		f_split_pipes(ms);
		node = ms->comand;
		exec_multi_node(node);
        // old_fd = g()->in_fd;
        // close(g()->in_fd);
        g()->in_fd = 0;
		// ft_print_details(ms);
		f_zero_list(ms);
		add_history(ms->line);
	}
	if (g()->export_list)
        ft_2darr_free(g()->export_list);
    if (g()->env_list)
        ft_2darr_free(g()->env_list);
	f_all_clean(ms, NULL);
	return (0);
}


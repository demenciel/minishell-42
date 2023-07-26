#include "../inc/minishell.h"

t_exec	*g(void)
{
	static t_exec	data;

	return (&data);
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

    size = 0;
    while (env[size])
        size++;
    g()->env_list = malloc(sizeof(char *) * (size + 1));
    if (!g()->env_list)
        return ;
    size = 0;
    while (env[size])
    {
        g()->env_list[size] = ft_strdup(env[size]);
        size++;
    }
    g()->env_list[size] = NULL;
}

void ft_print_details(t_meta *ms)
{
	if (DEBUG == 1)
		printf("\n=%s=\n\n", ms->line);
	f_check_line(ms);
	if (DEBUG == 1)
	{
		printf("\n");
		f_print_lst(ms->list);
		printf("\n");
	}
	f_check_node(ms);
	if (DEBUG == 1)
		printf("\n");
	f_split_pipes(ms);
	if (DEBUG == 1)
	{
		printf("\n");
		f_print_lst_final(ms->comand);
		printf("\n");
	}
}

int	main(int ac, char **av, char **env)
{
	t_meta *ms;
	t_comand *node;
	// (void)env;

	f_check_arg(ac, av);
	ms = f_init_meta();
    init_exec_struct();
    init_env(env);
	while (1)
	{
		ms->line = readline("minishell > ");
		f_check_line(ms);
		f_check_node(ms);
		f_split_pipes(ms);
		// ft_print_details(ms);
		if (ms->comand && ms->comand->com &&
		ft_strcmp(ms->comand->com[0], "exit") == 0)
			f_exit(ms);
		if (ms->error_flag == 0)
		{
			node = ms->comand;
			exec_multi_node(node);
			ms->exit_status = 0;
		}
		else
			ft_putstr_fd("salut la compagnie\n", 2);
        g()->in_fd = 0;
		add_history(ms->line);
		f_free_null_meta(ms);
	}
	f_all_clean(ms, NULL);
	return (0);
}


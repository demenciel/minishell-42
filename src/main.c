#include "../inc/minishell.h"

// PARSING

t_pipex	*g(void)
{
	static t_pipex	data;

	return (&data);
}

void	init_pipex(void)
{
	t_pipex	*p;

	p = g();
	p->in_fd = 0;
	p->out_fd = 0;
	p->exec_flag = 0;
	p->env_list = NULL;
	p->export_list = NULL;
}

/**
 * @brief Inits the environment, assigns it to env_list
 * @param env The computer environment
*/
void    init_env(char **env)
{
    int size;
    t_pipex *exec;

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

int	main(int ac, char **av, char **env)
{
	t_meta *ms;

	init_env(env);
	f_check_arg(ac, av);
	ms = f_init_meta();
	while (42)
	{
		ms->line = readline("minishell > ");
		printf("\n=%s=\n\n", ms->line);
		f_check_line(ms);
		printf("\n");
		f_print_lst(ms->list);
		printf("\n");
		f_split_pipes(ms);
		printf("\n");
		f_print_lst_final(ms->comand);
		// printf("com_temp =%s=", ms->com_temp);
		printf("\n");
		f_zero_list(ms);
		add_history(ms->line);
		if (ft_strncmp(ms->line, "exit", 4) == 0)
			break ;
	}
	if (g()->export_list)
        ft_2darr_free(g()->export_list);
    ft_2darr_free(g()->env_list);
	f_all_clean(ms, NULL);
	return (0);
}


#include "../inc/minishell.h"

t_exec	*g(void)
{
	static t_exec	data;

	return (&data);
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

void f_main_pars(t_meta *ms)
{
	f_check_line(ms);
	f_print_lst(ms->list); //TODO SUPPRIMER
	printf("\n");
	f_check_node(ms);
	f_split_pipes(ms);
	f_print_lst_final(ms->comand); //TODO SUPRIMER
	printf("\n");
	if (!ms->comand)
		ms->exit_status = 1;
}

int	main(int ac, char **av, char **env)
{
	t_meta *ms;

	f_check_arg(ac, av);
	ms = f_init_meta();
    init_exec_struct();
    init_env(env);
	f_signals();
	while (1)
	{
		ms->line = readline("minishell > ");
		if (ms->line == NULL)
			f_all_clean(ms, NULL);
		add_history(ms->line);
		f_main_pars(ms);
		if (ms->error_flag == 0)
		{
			if (ms->comand && (ft_check_builtins(ms) || check_comand(ms) == 0))
				exec_multi_node(ms);
		}

		f_free_null_meta(ms);
	}
	return (0);
}


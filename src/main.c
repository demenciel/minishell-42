
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

void	clean_fd()
{
	int i;

	i = 2;
	while (++i < 200)
		close(i);
}

void f_main_pars(t_meta *ms)
{
	f_check_line(ms);
	f_check_node(ms);
	f_split_pipes(ms);
	if (!ms->comand)
		ms->exit_status = 1;
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	char			*join_str;
	unsigned int	i;
	unsigned int	j;

	i = -1;
	j = 0;
	if ((!s1 && s2) || s1 == NULL)
		return((char*)s2);
	join_str = malloc(((ft_strlen(s1) + 1) + ft_strlen(s2)) * sizeof(char));
	if (!join_str)
		return (NULL);
	while (s1[++i])
		join_str[i] = s1[i];
	free(s1);
	while (s2[j])
		join_str[i++] = s2[j++];
	join_str[i] = '\0';
	return (join_str);
}

int	check_comand(t_meta *ms)
{
	int		i;
	int		flag;
	char	*search_cmd;
	char	**paths;
	char 	*error_node;
	t_comand *node;

	i = -1;
	node = ms->comand;
	if (node->com)
	{
		paths = get_env_path();
		if (!paths)
			return (-1);
		while (paths[++i])
			paths[i] = ft_strjoin_path(paths[i], "/");
		while (node)
		{
			i = -1;
			while (paths[++i])
			{
				flag = 0;
				search_cmd = ft_strjoin(paths[i], node->com[0]);
				if (access(search_cmd, 0) != 0)
					flag++;
				else
				{
					free(search_cmd);
					break ;
				}
				free(search_cmd);
			}
			if (flag > 0)
				error_node = ft_strdup(node->com[0]);
			node = node->next;
		}
		ft_2darr_free(paths);
		if (flag > 0)
		{
			printf("minishell: %s: command not found\n", error_node);
			free(error_node);
			return (-1);
		}
		else
			return (0);
	}
	return (0);
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
			{
				if (ms->comand->com != NULL)
					exec_multi_node(ms);
			}
		}

		f_free_null_meta(ms);
	}
	return (0);
}



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
	if (!ms->comand)
		ms->exit_status = 1;
	if (DEBUG == 1)
	{
		printf("\n");
		f_print_lst_final(ms->comand);
		printf("\n");
	}
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

int	check_comand(t_comand *com)
{
	int		i;
	int		flag;
	char	*search_cmd;
	char	**paths;
	char 	*error_node;

	i = -1;

	paths = get_env_path();
	while (paths[++i])
		paths[i] = ft_strjoin_path(paths[i], "/");
	while (com)
	{
		i = -1;
		while (paths[++i])
		{
			flag = 0;
			search_cmd = ft_strjoin(paths[i], com->com[0]);
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
			error_node = ft_strdup(com->com[0]);
		com = com->next;
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

int	main(int ac, char **av, char **env)
{
	t_meta *ms;
	t_comand *node;
	char	*temp;

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
		ft_print_details(ms);
		// if (ms->comand && ft_strncmp(ms->comand->com[0], "exit", 4) == 0)
		// 	f_exit(ms);
		// printf (" exit satus =%d=\n", ms->exit_status);
		// printf (" exit satus =%d=\n", ms->error_flag);
		if (ms->error_flag == 0)
		{
			if (ms->comand && (ft_check_builtins(ms->comand->com) || check_comand(ms->comand) == 0))
			{
				node = ms->comand;
				if (node->com != NULL)
					exec_multi_node(node);
				ms->exit_status = 0;
			}
		}
		else
		{
			temp = ft_strdup(f_error_message(ms->exit_status));
			printf("%s\n", temp);
			temp = f_freenull(temp);
		}
		f_free_null_meta(ms);
	}
	return (0);
}


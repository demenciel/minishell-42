/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:57:16 by acouture          #+#    #+#             */
/*   Updated: 2023/07/11 15:04:19 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int main(int ac, char **av, char **env)
{
    (void) ac;
    (void) av;

    // readline("> ");
    init_env(env);
    ft_export("HO$?LA=bonjour");
    // printf("------ EXPORT ------\n");
    // ft_export("");
    printf("------ ENV ------\n");
    ft_env();

    if (g()->export_list)
        ft_2darr_free(g()->export_list);
    ft_2darr_free(g()->env_list);
    return (0);
}

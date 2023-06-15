/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:57:16 by acouture          #+#    #+#             */
/*   Updated: 2023/06/15 16:34:54 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// PARSING

t_pipex	*call_struct(void)
{
	static t_pipex	data;

	return (&data);
}

void	init_pipex(void)
{
	t_pipex	*p;

	p = call_struct();
	p->in_fd = 0;
	p->out_fd = 0;
	p->exec_flag = 0;
	p->env_list = NULL;
	p->export_list = NULL;
}

int main(int ac, char **av)
{
    (void) ac;
    (void) av;
    t_meta  *ms;

    f_check_arg(ac, av);
    ms = f_init_meta();
    while (1)
    {
        ms->line = readline("minishel > ");
        printf ("\n%s\n\n", ms->line);
        f_check_line(ms);
        printf("\n");
        f_print_lst(ms->list);
        printf("\n");
        f_pars_list(ms);
         printf("\n");
        f_print_lst(ms->list);
        printf("\n");
        f_zero_list(ms);
        add_history(ms->line);
        if ( ft_strncmp(ms->line, "exit", 4) == 0)
            break ;
    }
    f_all_clean(ms, NULL);
    return (0);
}

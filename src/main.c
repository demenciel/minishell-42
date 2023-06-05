/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:57:16 by acouture          #+#    #+#             */
/*   Updated: 2023/06/05 10:10:10 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// PARSING
int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_meta  *ms;

    f_check_arg(ac, av);
    ms = f_init_meta();
    while (1)
    {
        ms->line = readline("minishel >");
        printf ("\n%s\n\n", ms->line);
        f_split_line(ms);
        f_print_lst(ms->list);
        printf("\n");
        f_zero_list(ms);
        add_history(ms->line);
        if ( ft_strncmp(ms->line, "exit", 4) == 0)
            break ;
    }
    return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:57:16 by acouture          #+#    #+#             */
/*   Updated: 2023/05/29 14:06:39 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// PARSING
int main( int ac, char **av)
{
    (void)ac;
    (void)av;

    char *line = NULL;
    while (1)
    {
        line = readline("minishel >");
        add_history(line);
    }
    return (0);
}
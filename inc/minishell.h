/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:57:03 by acouture          #+#    #+#             */
/*   Updated: 2023/06/05 10:11:06 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY
# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
// # include <readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/syscall.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>
# include "../libs/libft/include/libft.h"

// STRUCTURE-------------------------------------------------------------------

typedef struct s_parsing
{
	char				*txt;
	struct s_parsing	*next;
}			t_pars;

typedef struct s_meta
{
	size_t	lst_size;
	char	*line;
	t_pars	*list;
}			t_meta;

// LINK_LIST-----------------------------------------------------------------

t_pars	*f_new_node(char *str);
t_pars	*f_last_node(t_pars *list);
void	f_addback_node(t_pars **cmd, t_pars *new);
t_meta	*f_init_meta(void);
void	f_print_lst(t_pars *lst);

// PARSING---------------------------------------------------------------------

void f_check_arg(int ac, char ** av);

// UTILS-----------------------------------------------------------------------

void	f_split_line(t_meta *ms);
void	f_zero_list(t_meta *ms);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:57:03 by acouture          #+#    #+#             */
/*   Updated: 2023/06/06 14:23:54 by rofontai         ###   ########.fr       */
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

// COLOR-----------------------------------------------------------------------

# define BCK "\x1B[30m"
# define RED "\x1B[31m"
# define GRE "\x1B[32m"
# define YEL "\x1B[33m"
# define BLE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYA "\x1B[36m"
# define WHT "\x1B[37m"

// STRUCTURE-------------------------------------------------------------------

typedef struct s_parsing
{
	char				*txt;
	struct s_parsing	*next;
}			t_pars;

typedef struct s_meta
{
	char	*line;
	int		i;
	t_pars	*list;
}			t_meta;

// LINK_LIST-----------------------------------------------------------------

t_pars	*f_new_node(char *str);
t_pars	*f_last_node(t_pars *list);
void	f_addback_node(t_pars **cmd, t_pars *new);
void	f_print_lst(t_pars *lst);

// PARSING---------------------------------------------------------------------

void	f_check_arg(int ac, char ** av);
void	f_check_line(t_meta *ms);
void	f_check_pipes(t_meta *ms);
void	f_check_redir_right(t_meta *ms);
void	f_check_redir_left(t_meta *ms);
void	f_check_single_quote(t_meta *ms);
void	f_check_double_quote(t_meta *ms);
void	f_check_word(t_meta *ms);

// UTILS-----------------------------------------------------------------------

void	f_zero_list(t_meta *ms);
t_meta	*f_init_meta(void);

#endif
#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY
# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
// # include <readline.h>
# include "libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/syscall.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

// COLOR-----------------------------------------------------------------------

# define BCK "\x1B[30m"
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
}						t_pars;

typedef struct s_pipex
{
	int					in_fd;
	int					old_fd;
	int					out_fd;
	int					exec_flag;
	int					env_length;
	int					export_length;
	char				**env_list;
	char				**export_list;
}						t_pipex;

typedef struct s_meta
{
	char				*line;
	int					i;
	t_pars				*list;
}						t_meta;

// LINK_LIST-----------------------------------------------------------------

t_pars					*f_new_node(char *str);
t_pars					*f_last_node(t_pars *list);
void					f_addback_node(t_pars **cmd, t_pars *new);
void					f_print_lst(t_pars *lst);
void					f_free_list(t_pars **list);
void					f_free_meta(t_meta **ms);

// PARSING---------------------------------------------------------------------

void					f_check_arg(int ac, char **av);
void					f_check_line(t_meta *ms);
void					f_check_pipes(t_meta *ms);
void					f_check_redir_right(t_meta *ms);
void					f_check_redir_left(t_meta *ms);
void					f_check_single_quote(t_meta *ms);
void					f_check_double_quote(t_meta *ms);
void					f_check_word(t_meta *ms);
void					f_check_dollar(t_meta *ms);

// REDIRECT

void					redir_out(char *cmd, char *in, char *out);
void					redir_in(char *cmd, char *infile);
void					append_out(char *cmd, char *infile, char *output);
void					heredocs(char *limiter);

// PIPEX

void					pipex(char **cmd, int n, char *infile);
int						open_rd_fd(char *fd1);

// BUILTINS

void					ft_echo(char *string, int flag);
void					ft_cd(char *path);
void					ft_pwd(void);
void					ft_env(void);
void					ft_export(char *new_env);
void					ft_unset(char *var);

// EXPORT UTILS
void					add_var_to_list(char **new_var, int i, int *list_size);
char					*detect_var_export(char *var);
void					check_var(char *var);
void					ft_swap_char(char **a, char **b);
void					order_export(int *size);

// ERROR -----------------------------------------------------------------------
void					ft_exit(char *msg, char *builtin, int error);

// UTILS-----------------------------------------------------------------------

void					f_zero_list(t_meta *ms);
t_meta					*f_init_meta(void);
void					f_all_clean(t_meta *ms, char *msg);
t_pipex					*g(void);
void					init_pipex(void);
void					exec_cmd(char *cmd);

// CHECK_NODE------------------------------------------------------------------

char					*f_pars_dollar(char *txt);
void					f_pars_list(t_meta *ms);

// ERROR UTILS
void					print_error(char *cmd);
void					fd_error(char *fd);
void					pipex_fail(char *s);
void					cd_error(char *input);

#endif
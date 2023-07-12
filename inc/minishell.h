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
// # define RED "\x1B[31m"
# define GRE "\x1B[32m"
# define YEL "\x1B[33m"
# define BLE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYA "\x1B[36m"
# define WHT "\x1B[37m"

// STRUCTURE-------------------------------------------------------------------

typedef struct s_comand
{
	char				**com;
	char				*stin;
	char				*stout;
	struct s_comand		*next;
}						t_comand;

typedef struct s_parsing
{
	char				*txt;
	struct s_parsing	*next;
}						t_pars;

typedef struct s_meta
{
	char				*line;
	char				*com_temp;
	char				*in;
	char				*out;
	int					i;
	t_pars				*list;
	t_comand			*comand;
}						t_meta;

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

// REDIRECT

void					redir_out(char **cmd, char *in, char *out);
void					redir_in(char **cmd, char *infile);
void					append_out(char **cmd, char *infile, char *output);
void					heredocs(char *limiter);

// PIPEX

void					pipex(char **cmd, int n, char *infile);
int						open_rd_fd(char *fd1);

// BUILTINS

void					ft_check_builtins(t_comand *t_cmd);
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

t_pipex					*g(void);

void					init_pipex(void);
void					exec_cmd(char **cmd);

// ERROR UTILS
void					print_error(char *cmd);
void					fd_error(char *fd);
void					pipex_fail(char *s);
void					cd_error(char *input);

t_meta					*mt(void);

// PARSING---------------------------------------------------------------------

void					f_check_arg(int ac, char **av);
void					f_check_line(t_meta *ms);
void					f_check_word(t_meta *ms);
void					f_check_dollar(t_meta *ms);

// CHECK-----------------------------------------------------------------------

void					f_check_pipes(t_meta *ms);
void					f_check_redir_right(t_meta *ms);
void					f_check_redir_left(t_meta *ms);
void					f_check_single_quote(t_meta *ms);
void					f_check_double_quote(t_meta *ms);

// UTILS-----------------------------------------------------------------------

t_meta					*f_init_meta(void);
void					f_all_clean(t_meta *ms, char *msg);
void					f_zero_list(t_meta *ms);
char					*f_trimstr(char *s1, char c);
void					f_free_comand(t_comand **list);

// PARS------------------------------------------------------------------------

int						f_som_quote_simple(char *txt);
char					*f_pars_simple_quote(t_meta *ms, char *txt);
char					*f_pars_dollar(char *txt);
char					*f_pars_double_quote(t_meta *ms, char *txt);
int						f_som_quote_double(char *txt);

// LINKS_LIST------------------------------------------------------------------

void					f_free_list(t_pars **list);
t_pars					*f_new_node(char *str);
t_pars					*f_last_node(t_pars *list);
void					f_addback_node(t_pars **cmd, t_pars *new);

// COM_LIST--------------------------------------------------------------------

t_comand				*f_new_com(char *com, char *in, char *out);
t_comand				*f_last_com(t_comand *list);
void					f_addback_com(t_comand **cmd, t_comand *new);
void					f_split_pipes(t_meta *ms);
void					f_zero_new_com(t_meta *ms);

// UTILS_COM-------------------------------------------------------------------

void					f_add_com(t_meta *ms, char *add);
void					f_add_in(t_meta *ms, char *add);
void					f_add_out(t_meta *ms, char *add);

// A_SUPP----------------------------------------------------------------------

void					f_print_lst(t_pars *lst);
void					f_print_lst_final(t_comand *lst);
void					f_print(char **cou);

#endif
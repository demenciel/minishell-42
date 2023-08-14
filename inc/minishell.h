/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:35:21 by acouture          #+#    #+#             */
/*   Updated: 2023/08/14 11:34:44 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY
# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include "history.h"
# include "readline.h"
# include "libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
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

# define DEBUG 0
# define HEREDOC_SUCCESS 11
# define HEREDOC_ERROR -2
# define FD_ERROR -3
# define EXEC_ERROR -14
# define MALLOC_ERROR -5

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
	int					exit_status;
	int					error_flag;
}						t_meta;

typedef struct s_exec
{
	pid_t				*pid;
	bool				redir_flag;
	int					pid_index;
	int					in_fd;
	int					old_fd;
	int					out_fd;
	int					pipe_end[2];
	int					env_length;
	int					export_length;
	char				**env_list;
	char				**export_list;
}						t_exec;

// MAIN CHECK
char					*ft_strjoin_path(char *s1, char *s2);
char					*ft_strjoin_path(char *s1, char *s2);
int						check_absolute_path(char **cmd);
int						check_comand(t_meta *ms);
char					**command_path(void);
int						check_comand_norm(t_meta *ms, t_comand *node,
							char **paths);
int						search_cmd_path(t_comand *node, char *path, int flag);
int						check_cmd_error(t_meta *ms, int flag, char *error_node);

// REDIRECT
int						redirect_nodes(int *pipe, t_meta *ms);
int						redirect_out(t_meta *ms);
int						redirect_in(t_meta *ms, int *pipe);
int						heredocs(char *limiter, int input_fd);

// PIPEX
void					pipex(t_meta *ms, bool multi, int input_fd, int out_fd);
int						open_rd_fd(t_meta *ms, char *fd1);
int						create_rd_fd(t_meta *ms, char *fd1);
int						append_rd_fd(t_meta *ms, char *fd1);

// MAIN EXEC UTILS
void					wait_free_pid(t_meta *ms, int nb_node);
int						lst_size(t_comand *lst);
void					init_exec_struct(void);
void					clean_fd(void);
int						check_for_path(void);

// MAIN EXEC
void					exec_multi_node(t_meta *ms);
char					**get_env_path(void);

// EXEC BUILTINS
bool					ft_check_builtins(t_meta *ms);
void					find_builtins(t_meta *ms, int input_fd);
void					find_export_env(t_meta *ms, int input_fd);

// BUILTINS
void					ft_echo(char *string, int input_fd);
char					*ft_pwd(void);
void					ft_env(int fd);
void					ft_export(t_meta *ms, char *new_env, int fd);
void					ft_unset_env(char *var);
void					ft_unset_export(char *var);

// ECHO
void					find_echo(t_meta *ms, int input_fd);
int						iterate_over_echo_flag(t_meta *ms, int i);
char					*ft_strtrim_echo(char const *s1, char const *set);

// CD
void					ft_cd(t_meta *ms, char *path);
char					*get_env(char *input);
void					replace_oldpwd(char *oldpath);
void					change_pwd_env(char *oldpath, char *path);
char					*result_path(t_meta *ms, char *env_var, bool oldpwd);
char					*path_to_cd(t_meta *ms, char *path);

// ENV
char					**ft_cpy_env(char **list);
void					change_var_content_export(char *var, int index);
int						checks_for_doubles_env(char *var);
void					add_var_to_env(char *new_var, int i);

// EXPORT UTILS
void					add_var_to_export(char *new_var, int i, int *list_size);
int						checks_for_doubles_export(char *var);
void					change_var_content_export(char *var, int index);
char					*detect_var_export(char *var);
char					**ft_cpy_export(char **list);
void					add_var_to_env(char *new_var, int i);
int						check_var(t_meta *ms, char *var);
void					ft_swap_char(char **a, char **b);
void					order_export(int *size);

// UTILS

t_exec					*g(void);
t_meta					*mt(void);
void					exec_cmd(t_meta *ms, char **cmd);

// ERROR UTILS
void					print_error(t_meta *ms, char *cmd);
void					fd_error(t_meta *ms, char *fd);
void					pipex_fail(t_meta *ms, char *s);
void					cd_error(t_meta *ms, char *input);
void					export_error(t_meta *ms, char *id);

//PARSING-MINISHELL

// CHECKING_1------------------------------------------------------------------

void					f_check_word(t_meta *ms);
void					f_check_single_quote(t_meta *ms);
char					*f_pars_simple_quote(t_meta *ms, char *txt);
int						f_size_list(t_pars *lst);
void					f_new_check_dollar(t_meta *ms);

// CHECKING_2------------------------------------------------------------------

void					f_check_double_quote(t_meta *ms);
void					f_check_redir_left(t_meta *ms);
void					f_check_redir_right(t_meta *ms);
void					f_check_pipes(t_meta *ms);

// CHECKING_3-------------------------------------------------------------------

char					*ft_strjoin_f(char *s1, const char *s2);
char					*f_copy(char *temp, t_meta *ms);
char					*f_copy_doll(int *i, char *temp, char *txt, t_meta *ms);
char					*f_pars_dollar(t_meta *ms, char *txt);

// CHECKING--------------------------------------------------------------------

char					*f_pars_new_dollar(t_meta *ms, char *txt);
char					*f_cut(int *i, char *temp, t_meta *ms, char *txt);
char					*f_cut_plus(int *start, int *i, char *temp, char *txt);
int						f_check_quote_double_ok(t_meta *ms, char *txt);
char					*f_pars_double_quote(t_meta *ms, char *txt);

// COM_LIST--------------------------------------------------------------------

t_comand				*f_new_com(char *com, char *in, char *out);
void					f_zero_new_com(t_meta *ms);
t_comand				*f_last_com(t_comand *list);
void					f_addback_com(t_comand **cmd, t_comand *new);
void					f_split_pipes(t_meta *ms);

// COM_UTILS-------------------------------------------------------------------

void					f_add_com(t_meta *ms, char *add);
void					f_add_in(t_meta *ms, char *add);
void					f_add_out(t_meta *ms, char *add);
void					f_check_node(t_meta *ms);
int						f_search_dollar(char *str);

// EXIT------------------------------------------------------------------------

int						find_exit(t_meta *ms, int fd);
int						f_size_table(char **table);
int						f_arg_is_num(char *txt);
void					f_message(t_meta *ms, char *txt, int fd);
void					f_message_short(int fd);

// FREE------------------------------------------------------------------------

void					f_free_null_meta(t_meta *ms);
void					f_free_comand(t_comand **list);
void					f_free_list(t_pars **list);
void					*f_freenull(void *str);

// INIT------------------------------------------------------------------------

t_meta					*f_init_meta(void);
void					f_all_clean(t_meta *ms, char *msg);
void					f_all_clean_exit(t_meta *ms, int nb);
void					f_free_exit_child(t_meta *ms, int nb);
void					f_free_meta(t_meta *ms);

// PARSING---------------------------------------------------------------------

void					f_check_arg(int ac, char **av);
void					f_check_line(t_meta *ms);
void					f_cut_add_out(t_meta *ms, t_pars **temp);
void					f_cut_add_in(t_meta *ms, t_pars **temp);
void					f_print_error(t_meta *ms);

// SIGNAL----------------------------------------------------------------------

void					f_sighandler(int sig);
void					f_sighandler_com(int sig);
void					f_signals(void);
void					f_signal_in(int status, t_meta *ms);
void					f_exit_syntax_error(t_meta *ms, int flag);

// UTILS_1---------------------------------------------------------------------

int						f_som_quote_simple(char *txt);
int						f_check_env(char c);
int						f_check_env_dol(char c);
int						f_som_quote_double(char *txt);
char					*f_join_char(const char *s1, const char s2);

// UTILS-----------------------------------------------------------------------

t_pars					*f_new_node(char *str);
t_pars					*f_last_node(t_pars *list);
void					f_addback_node(t_pars **cmd, t_pars *new);
int						f_check_metachar(char c);
char					*f_trimstr(char *s1, char c);

#endif

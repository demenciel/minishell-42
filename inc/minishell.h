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
	int					exec_flag;
	int					env_length;
	int					export_length;
	char				**env_list;
	char				**export_list;
}						t_exec;

// REDIRECT

int						redirect_out(t_comand *node);
int						redirect_in(t_comand *node, int *pipe);
int						heredocs(char *limiter, int input_fd);

// PIPEX
pid_t	pipex(t_comand *node, bool multi, int input_fd, int out_fd);
int						open_rd_fd(char *fd1);
int						create_rd_fd(char *fd1);
int						append_rd_fd(char *fd1);
void					wait_free_pid(int nb_node);

// MAIN EXEC
void					exec_multi_node(t_comand *node);
void					init_exec_struct(void);
int	lst_size(t_comand *lst);
char	**get_env_path(void);
void	clean_fd();

// EXEC BUILTINS
bool					ft_check_builtins(char **cmd);
void					find_builtins(t_comand *node, int input_fd);
void					find_export_unset_env(t_comand *node, int input_fd);

// BUILTINS
void					ft_echo(char *string, int input_fd);
char					*ft_pwd(void);
void					ft_env(int fd);
void					ft_export(char *new_env, int fd);
void					ft_unset_env(char *var);
void					ft_unset_export(char *var);

// CD
void					ft_cd(char *path);
char					*get_env(char *input);
void					replace_oldpwd(char *oldpath);
void	change_pwd_env(char *oldpath, char *path);
char					*result_path(char *env_var, char *path_env,
							bool oldpwd);

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
int						check_var(char *var);
void					ft_swap_char(char **a, char **b);
void					order_export(int *size);

// ERROR -----------------------------------------------------------------------
void					ft_exit(char *msg, char *builtin, int error);

// UTILS-----------------------------------------------------------------------

t_exec					*g(void);
void					exec_cmd(char **cmd);

// ERROR UTILS
void					print_error(char *cmd);
void					fd_error(char *fd);
void					pipex_fail(char *s);
void					cd_error(char *input);

t_meta					*mt(void);

//PARSING-MINISHELL

// PARSING---------------------------------------------------------------------

void					f_check_arg(int ac, char **av);
void					f_check_line(t_meta *ms);

// CHECKING--------------------------------------------------------------------

void					f_check_word(t_meta *ms);
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
char					*f_pars_new_dollar(t_meta *ms, char *txt);
void 					f_new_check_dollar(t_meta *ms);
char					*f_pars_dollar(t_meta *ms, char *txt);
void					f_check_double_quote(t_meta *ms);
char					*f_pars_double_quote(t_meta *ms, char *txt);
void					f_check_redir_left(t_meta *ms);
void					f_check_redir_right(t_meta *ms);
void					f_check_pipes(t_meta *ms);

// UTILS-----------------------------------------------------------------------

t_pars					*f_new_node(char *str);
t_pars					*f_last_node(t_pars *list);
void					f_addback_node(t_pars **cmd, t_pars *new);
int						f_check_metachar(char c);
char					*f_trimstr(char *s1, char c);
int						f_som_quote_simple(char *txt);
int						f_check_env(char c);
int						f_som_quote_double(char *txt);
char					*f_join_char(const char *s1, const char s2);
int						f_check_env_dol(char c);
char					**f_check_command(char *str);
int						f_exec_cmd(char **cmd);
int						f_search_dollar(char *str);

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

// INIT------------------------------------------------------------------------

t_meta					*f_init_meta(void);

// FREE------------------------------------------------------------------------

void					f_free_null_meta(t_meta *ms);
void					f_free_comand(t_comand **list);
void					f_free_list(t_pars **list);
void					*f_freenull(void *str);
void					f_all_clean(t_meta *ms, char *msg);
void					f_all_clean_exit(t_meta *ms, int nb);
void					f_free_exit_child(t_meta *ms, int nb);

// A_SUPP----------------------------------------------------------------------

void					f_print_lst(t_pars *lst);
void					f_print_lst_final(t_comand *lst);
void					f_print(char **cou);


// EXIT------------------------------------------------------------------------

int						f_exit(t_meta *ms);
int						f_size_table(char **table);
int						f_arg_is_num(char *txt);
char					*f_error_message(int nb);

// SIGNAL----------------------------------------------------------------------

void	f_sighandler(int sig);
void	f_sighandler_com(int sig);
void	f_signals(int nb);

#endif
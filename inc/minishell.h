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


// STRUCTURE-------------------------------------------------------------------

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

t_pipex					*g(void);
void					init_pipex(void);
void					exec_cmd(char *cmd);

// ERROR UTILS
void					print_error(char *cmd);
void					fd_error(char *fd);
void					pipex_fail(char *s);
void					cd_error(char *input);

#endif
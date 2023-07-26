

#include "../../inc/minishell.h"

void	print_error(char *cmd)
{
	printf("minishell: command not found: %s\n", cmd);
}

void	cd_error(char *input)
{
	printf("cd: %s: No such file or directory\n", input);
}

void	fd_error(char *fd)
{
	printf("minishell: No such file or directory: %s\n", fd);
}

void	pipex_fail(char *s)
{
	perror(s);
	exit(1);
}

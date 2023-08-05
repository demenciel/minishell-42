

#include "../../inc/minishell.h"

void	print_error(char *cmd)
{
	printf("minishell: command not found: %s\n", cmd);
}

void	cd_error(char *input)
{
	write(2, "minishell: cd: ", 16);
	write(2, input, ft_strlen(input));
	write(2, ": no such file or directory\n", 29);
	mt()->exit_status = 1;
	mt()->error_flag = 1;
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


#include "../../inc/minishell.h"

/**
 * @brief Reproduce the env builtin command (env)
*/
void	ft_env(int fd)
{
	ft_2darr_print(g()->env_list, fd);
}

/**
 * @brief Reproduce the echo builtin command (echo)
*/
void	ft_echo(char *string, int input_fd)
{
	ft_putstr_fd(string, input_fd);
}

/**
 * @brief Reproduce the pwd builtin command (pwd)
*/
char	*ft_pwd(void)
{
	char *pwd;

	pwd = NULL;
	pwd = get_env("PWD=");
	return (pwd);
}

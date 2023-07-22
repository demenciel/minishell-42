
#include "../../inc/minishell.h"

/**
 * @brief Reproduce the env builtin command (env)
*/
void    ft_env(int fd)
{
    ft_2darr_print(g()->env_list, fd);
}

/**
 * @brief Reproduce the echo builtin command (echo)
*/
void    ft_echo(char *string, int input_fd)
{
    ft_putstr_fd(string, input_fd);
    ft_putchar_fd('\n', input_fd);
}

/**
 * @brief Depending on the input, finds the ENV VAR
*/
char	*get_env(char *input)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (g()->env_list[i])
	{
		if (ft_strncmp(input, g()->env_list[i], ft_strlen(input)) == 0)
			break ;
		i++;
	}
    path = ft_strtrim(g()->env_list[i], ft_strjoin(input, "="));
	return (path);
}

void    replace_oldpwd(char *oldpath)
{
    int i;

    i = 0;
	while (g()->env_list[i])
	{
		if (ft_strncmp("OLDPWD", g()->env_list[i], 6) == 0)
			break ;
		i++;
	}
    free(g()->env_list[i]);
    g()->env_list[i] = ft_strjoin("OLDPWD=", oldpath);
}

/**
 * @brief Reproduce the cd builtin command (cd)
 * @param path The directory to go to
*/
void ft_cd(char *path)
{
    char *path_env;
    char *oldpath;
    
    oldpath = ft_strdup(ft_pwd());
    if (!path || *path == '\0')
    {
        path_env = get_env("HOME");
        if (!path_env)
        {
            cd_error("HOME");
            return;
        }
        path = path_env;
    }
    else if (ft_strncmp(path, "-", sizeof(path)) == 0)
    {
        path_env = get_env("OLDPWD");
        if (!path_env)
        {
            cd_error("OLDPWD");
            return ;
        }
        path = path_env;
    }
    else if (chdir(path) == -1)
        cd_error(path);
    replace_oldpwd(oldpath);
    free(path);
    free(oldpath);
}

/**
 * @brief Reproduce the pwd builtin command (pwd)
*/
char *ft_pwd(void)
{
    char buf[PATH_MAX];
    char *pwd;

    pwd = getcwd(buf, sizeof(buf));
    return(pwd);
}
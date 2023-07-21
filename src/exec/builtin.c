
#include "../../inc/minishell.h"

/**
 * @brief Reproduce the env builtin command (env)
*/
void    ft_env(int fd)
{
    int i;

    i = 0;
    ft_2darr_print(g()->env_list, fd);
}

/**
 * @brief Reproduce the echo builtin command (echo)
*/
void    ft_echo(char *string, int flag)
{
    if (flag)
        printf("%s", string);
    else
        printf("%s\n", string);
}

/**
 * @brief Reproduce the cd builtin command (cd)
 * @param path The directory to go to
*/
void ft_cd(char *path)
{
    char *path_env;

    if (!path)
    {
        path_env = getenv("HOME");
        if (!path_env)
        {
            cd_error("HOME");
            return;
        }
        path = path_env;
    }
    else if (ft_strncmp(path, "-", sizeof(path)) == 0)
    {
        path_env = getenv("OLDPWD");
        if (!path_env)
        {
            cd_error("OLDPWD");
            return ;
        }
        path = path_env;
    }
    else if (chdir(path) == -1)
        cd_error(path);
}

/**
 * @brief Reproduce the pwd builtin command (pwd)
*/
void ft_pwd(void)
{
    char buf[PATH_MAX];

    printf("%s\n", getcwd(buf, sizeof(buf)));
}
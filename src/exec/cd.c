
#include "../../inc/minishell.h"

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
	path = ft_strtrim(g()->env_list[i], input);
	return (path);
}

void	replace_oldpwd(char *oldpath)
{
	int	i;

	i = 0;
	while (g()->env_list[i])
	{
		if (ft_strncmp("OLDPWD", g()->env_list[i], 6) == 0)
			break ;
		i++;
	}
	free(g()->env_list[i]);
	g()->env_list[i] = ft_strjoin("OLDPWD=", oldpath);
	free(oldpath);
}

void	change_pwd_env(char *oldpath, char *path)
{
	int		i;
	char	*chpwd;
	char	*pwd;
	char buf[PATH_MAX];

	i = 0;
	while (g()->env_list[i])
	{
		if (ft_strncmp("PWD", g()->env_list[i], 3) == 0)
			break ;
		i++;
	}
	free(g()->env_list[i]);
	chpwd = ft_strjoin("/", path);
	if (getcwd(buf, sizeof(buf)))
		pwd = ft_strdup(buf);
	else
		pwd = ft_strjoin(oldpath, chpwd);
	g()->env_list[i] = ft_strjoin("PWD=", pwd);
	free(pwd);
	free(chpwd);
}

char	*result_path(char *env_var, char *path_env, bool oldpwd)
{
	char	*result;

	result = NULL;
	path_env = get_env(env_var);
	if (!path_env)
	{
		cd_error(env_var);
		return (NULL);
	}
	if (oldpwd)
		printf("%s\n", path_env);
	result = path_env;
	return (result);
}

/**
 * @brief Reproduce the cd builtin command (cd)
 * @param path The directory to go to
*/
void	ft_cd(char *path)
{
	char *result;
	char *path_env;
	char *oldpath;
	
	result = NULL;
	path_env = NULL;
	oldpath = NULL;
	if (!path || *path == '\0')
		result = result_path("HOME=", path_env, false);
	else if (ft_strcmp(path, "-") == 0)
		result = result_path("OLDPWD=", path_env, true);
	else
		result = ft_strdup(path);
	oldpath = ft_pwd();
	if (oldpath == NULL)
		return ;
	if (chdir(result) == -1)
		cd_error(result);
	change_pwd_env(oldpath, path);
	replace_oldpwd(oldpath);
	free(result);
}

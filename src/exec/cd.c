/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:02:34 by acouture          #+#    #+#             */
/*   Updated: 2023/08/08 14:02:35 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Depending on the input, finds the ENV VAR
 */
char	*get_env(char *input)
{
	bool	found;
	char	*path;
	char	*new_path;
	int		i;

	i = 0;
	new_path = NULL;
	while (g()->env_list[i])
	{
		if (ft_strncmp(input, g()->env_list[i], ft_strlen(input)) == 0)
		{
			found = true;
			break ;
		}
		else
			found = false;
		i++;
	}
	if (found)
	{
		path = ft_strtrim(g()->env_list[i], input);
		new_path = ft_strtrim(path, "=");
		path = f_freenull(path);
	}
	return (new_path);
}

/**
 * @brief Function to replace the OLDPWD in the env
 * @param oldpath The OLDPATH path
 */
void	replace_oldpwd(char *oldpath)
{
	int		i;
	bool	found;
	t_exec	*p;

	i = 0;
	p = g();
	while (p->env_list[i])
	{
		if (ft_strncmp("OLDPWD", p->env_list[i], 6) == 0)
		{
			found = true;
			break ;
		}
		else
			found = false;
		i++;
	}
	if (false)
	{
		free(p->env_list[i]);
		p->env_list[i] = ft_strjoin("OLDPWD=", oldpath);
		free(oldpath);
	}
}

/**
 * @brief Function to change the PWD in the env
 */
void	change_pwd_env(char *oldpath, char *path)
{
	int		i;
	t_exec	*p;
	char	*chpwd;
	char	*pwd;
	char	buf[PATH_MAX];

	i = 0;
	p = g();
	while (p->env_list[i])
	{
		if (ft_strncmp("PWD", p->env_list[i], 3) == 0)
			break ;
		i++;
	}
	free(p->env_list[i]);
	chpwd = ft_strjoin("/", path);
	if (getcwd(buf, sizeof(buf)))
		pwd = ft_strdup(buf);
	else
		pwd = ft_strjoin(oldpath, chpwd);
	p->env_list[i] = ft_strjoin("PWD=", pwd);
	free(pwd);
	free(chpwd);
}

char	*result_path(char *env_var, bool oldpwd)
{
	char	*result;
	char	*path_env;

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
 * @brief Based on the input, iterates over the env and gets the path needed
 * @param path Input of cd
 * @return Returns NULL if path is not find, otherwise, returns the path found
 */
char	*path_to_cd(char *path)
{
	char	*result;

	result = NULL;
	if (!path || *path == '\0')
		result = result_path("HOME=", false);
	else if (ft_strcmp(path, "-") == 0)
		result = result_path("OLDPWD=", true);
	else
		result = ft_strdup(path);
	return (result);
}

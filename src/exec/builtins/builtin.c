/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:54:59 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 17:10:52 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
	char	*pwd;

	pwd = NULL;
	pwd = get_env("PWD=");
	return (pwd);
}

/**
 * @brief Reproduce the cd builtin command (cd)
 * @param path The directory to go to
 */
void	ft_cd(t_meta *ms, char *path)
{
	char	*result;
	char	*oldpath;

	oldpath = NULL;
	oldpath = ft_pwd();
	result = path_to_cd(ms, path);
	if (result == NULL)
	{
		free(oldpath);
		ms->exit_status = 127;
		ms->error_flag = 1;
		return ;
	}
	if (oldpath == NULL)
		return ;
	if (chdir(result) == -1)
		cd_error(ms, result);
	change_pwd_env(oldpath, path);
	replace_oldpwd(oldpath);
	free(oldpath);
	free(result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 07:43:03 by acouture          #+#    #+#             */
/*   Updated: 2023/08/11 14:25:52 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Checks the content of the node,
	and executes the builtin depending of the content of the node
*/
void	find_unset(t_meta *ms)
{
	int		i;
	char	*joined;

	if (ft_strcmp(ms->comand->com[0], "unset") == 0)
	{
		i = 1;
		if (!ms->comand->com[i])
			return ;
		while (ms->comand->com[i])
		{
			if (check_var(ms, ms->comand->com[i]) != 0)
				return ;
			joined = ft_strjoin(ms->comand->com[i], "=");
			ft_unset_export(joined);
			ft_unset_env(joined);
			free(joined);
			i++;
		}
	}
}

/**
 * @brief Checks the content of the node,
	and executes the builtin depending of the content of the node
*/
void	find_export_env(t_meta *ms, int input_fd)
{
	int	i;

	if (ft_strcmp(ms->comand->com[0], "export") == 0)
	{
		i = 1;
		if (!ms->comand->com[i])
			ft_export(ms, "", input_fd);
		while (ms->comand->com[i])
			ft_export(ms, ms->comand->com[i++], input_fd);
	}
	else if (ft_strcmp(ms->comand->com[0], "env") == 0)
		ft_env(input_fd);
}

/**
 * @brief Checks the content of the node,
	and executes the builtin depending of the content of the node
*/
void	find_cd_pwd(t_meta *ms, int input_fd)
{
	char	*pwd;

	if (ft_strcmp(ms->comand->com[0], "cd") == 0)
	{
		if (!ms->comand->com[1])
			ft_cd(ms, "");
		else
			ft_cd(ms, ms->comand->com[1]);
	}
	if (ft_strcmp(ms->comand->com[0], "pwd") == 0)
	{
		pwd = ft_pwd();
		if (!pwd)
			return ;
		ft_putstr_fd(pwd, input_fd);
		ft_putchar_fd('\n', input_fd);
		free(pwd);
	}
}

/**
 * @brief A function to separate the execution of the builtins
 */
void	find_builtins(t_meta *ms, int input_fd)
{
	find_export_env(ms, input_fd);
	find_unset(ms);
	find_cd_pwd(ms, input_fd);
	find_echo(ms, input_fd);
	find_exit(ms, input_fd);
}

/**
 * @brief Iterates in the comand linked list to find the builtins to execute
 */
bool	ft_check_builtins(t_meta *ms)
{
	if (ms->comand->com)
	{
		if (ft_strncmp(ms->comand->com[0], "unset", ft_strlen("unset\n")) == 0)
			return (true);
		else if (ft_strncmp(ms->comand->com[0], "export",
				ft_strlen("export\n")) == 0)
			return (true);
		else if (ft_strncmp(ms->comand->com[0], "env", ft_strlen("env\n")) == 0)
			return (true);
		else if (ft_strncmp(ms->comand->com[0], "echo",
				ft_strlen("echo\n")) == 0)
			return (true);
		else if (ft_strncmp(ms->comand->com[0], "cd", ft_strlen("cd\n")) == 0)
			return (true);
		else if (ft_strncmp(ms->comand->com[0], "pwd", ft_strlen("pwd\n")) == 0)
			return (true);
		else if (ft_strncmp(ms->comand->com[0], "exit",
				ft_strlen("exit\n")) == 0)
			return (true);
	}
	return (false);
}

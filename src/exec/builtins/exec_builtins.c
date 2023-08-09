/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 07:43:03 by acouture          #+#    #+#             */
/*   Updated: 2023/08/09 10:06:56 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Checks the content of the node,
	and executes the builtin depending of the content of the node
*/
void	find_export_unset_env(t_comand *node, int input_fd)
{
	int	i;

	if (ft_strcmp(node->com[0], "export") == 0)
	{
		i = 1;
		if (!node->com[i])
			ft_export("", input_fd);
		while (node->com[i])
			ft_export(node->com[i++], input_fd);
	}
	else if (ft_strcmp(node->com[0], "unset") == 0)
	{
		i = 1;
		if (!node->com[i])
			return ;
		while (node->com[i])
		{
			ft_unset_export(node->com[i]);
			ft_unset_env(node->com[i]);
			i++;
		}
	}
	else if (ft_strcmp(node->com[0], "env") == 0)
		ft_env(input_fd);
}

/**
 * @brief Checks the content of the node,
	and executes the builtin depending of the content of the node
*/
void	find_cd_pwd(t_comand *node, int input_fd)
{
	char	*pwd;

	if (ft_strcmp(node->com[0], "cd") == 0)
	{
		if (!node->com[1])
			ft_cd("");
		else
			ft_cd(node->com[1]);
	}
	if (ft_strcmp(node->com[0], "pwd") == 0)
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
void	find_builtins(t_comand *node, int input_fd)
{
	find_exit(node, mt());
	find_export_unset_env(node, input_fd);
	find_cd_pwd(node, input_fd);
	find_echo(node, input_fd);
}

/**
 * @brief Iterates in the comand linked list to find the builtins to execute
 */
bool	ft_check_builtins(char **cmd)
{
	if (mt()->comand)
	{
		if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
			return (true);
		else if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
			return (true);
		else if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
			return (true);
		else if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0)
			return (true);
		else if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
			return (true);
		else if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
			return (true);
		else if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0)
			return (true);
	}
	return (false);
}

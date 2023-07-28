#include "../../inc/minishell.h"

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
 * @brief Checks the content of the node,
	and executes the builtin depending of the content of the node
*/
void	find_echo(t_comand *node, int input_fd)
{
	char	*echo_string;
	int		i;
	int 	flag = 0;

	if (ft_strcmp(node->com[0], "echo") == 0)
	{
		if (ft_strcmp(node->com[1], "-n") == 0)
		{
			i = 2;
			flag = 1;
		}
		else
			i = 1;
		echo_string = NULL;
		while (node->com[i])
		{
			if (ft_strncmp(node->com[i], "-n", 2) == 0)
				break ;
			echo_string = ft_strjoin(node->com[i], " ");
			ft_echo(echo_string, input_fd);
			if (flag == 0)
				ft_putchar_fd('\n', input_fd);
			free(echo_string);
			i++;
		}
	}
}

/**
 * @brief A function to separate the execution of the builtins
*/
void	find_builtins(t_comand *node, int input_fd)
{
	find_export_unset_env(node, input_fd);
	find_cd_pwd(node, input_fd);
	find_echo(node, input_fd);
}

/**
 * @brief Iterates in the comand linked list to find the builtins to execute
*/
bool	ft_check_builtins(char **cmd)
{
	if (ft_strncmp(cmd[0], "export", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		return (true);
	return (false);
}

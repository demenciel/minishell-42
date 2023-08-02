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
char	*ft_strtrim_echo(char const *s1, char const *set)
{
	char	*new_str;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	new_str = (char *)malloc((end - start) + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1 + start, end - start + 1);
	return (new_str);
}

int iterate_over_echo_flag(t_comand *node, int i)
{
	t_comand *temp;
	char *trim;
	int j;

	j = i;
	temp = node;
	while (node->com[j])
	{
		trim = ft_strtrim_echo(node->com[j], "-");
		if (!(ft_strchr(trim, '-')))
		{
			if (ft_strcmp("n", trim) == 0)
				i++;
			else
			{
				free(trim);	
				break;
			}
		}
		j++;
		free(trim);
	}
	return (i);
}


/**
 * @brief Checks the content of the node,
	and executes the builtin depending of the content of the node
*/
void	find_echo(t_comand *node, int input_fd)
{
	char	*echo_string;
	int		i = 1;
	int 	flag = 0;
	char 	*trim;

	if (ft_strcmp(node->com[0], "echo") == 0)
	{
		if (!node->com[1])
		{
			ft_putchar_fd('\n', input_fd);
			return ;
		}
		if (ft_strcmp("-n", node->com[1]) == 0)
		{
			trim = ft_strtrim_echo(node->com[1], "-");
			if (!(ft_strchr(trim, '-')))
			{
				i = 2;
				i = iterate_over_echo_flag(node, i);
				flag = 1;
			}
			free(trim);
		}
		echo_string = NULL;
		while (node->com[i])
		{
			if (ft_strncmp(node->com[1], "-n", ft_strlen(node->com[1])) == 0 && !node->com[2])
				break ;
			if (node->next == NULL && node == NULL )
				echo_string = ft_strdup(node->com[i]);
			else
				echo_string = ft_strjoin(node->com[i], " ");
			ft_echo(echo_string, input_fd);
			free(echo_string);
			i++;
		}
		if (!(flag > 0))
			ft_putchar_fd('\n', input_fd);
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

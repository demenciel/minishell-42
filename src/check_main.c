/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:50:34 by acouture          #+#    #+#             */
/*   Updated: 2023/08/14 15:02:43 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Function to print an error if the input of export is not valid
 */
void	cmd_error(t_meta *ms, char *id)
{
	write(2, "minishell: ", 12);
	write(2, id, ft_strlen(id));
	write(2, ": command not found\n", 21);
	ms->exit_status = 127;
	ms->error_flag = 1;
}

int	check_cmd_error(t_meta *ms, int flag, char *error_node)
{
	if (flag > 0)
	{
		cmd_error(ms, error_node);
		free(error_node);
		return (-1);
	}
	else
		return (0);
}

int	search_cmd_path(t_comand *node, char *path, int flag)
{
	char	*search_cmd;

	flag = 0;
	search_cmd = ft_strjoin(path, node->com[0]);
	if (access(search_cmd, X_OK) != 0)
		flag++;
	else
	{
		free(search_cmd);
		return (0);
	}
	free(search_cmd);
	return (flag);
}

int	check_comand_norm(t_meta *ms, t_comand *node, char **paths)
{
	int		flag;
	int		i;
	char	*error_node;

	while (node)
	{
		i = -1;
		if (check_absolute_path(node->com) == 0)
			return (0);
		while (paths[++i])
		{
			flag = search_cmd_path(node, paths[i], flag);
			if (flag == 0)
				break ;
		}
		if (flag > 0)
			error_node = ft_strdup(node->com[0]);
		node = node->next;
	}
	return (check_cmd_error(ms, flag, error_node));
}

int	check_comand(t_meta *ms)
{
	char		**paths;
	t_comand	*node;
	int			return_norm;

	node = ms->comand;
	if (node->com)
	{
		if (check_node_cmd(ms, node->com[0]) == -1)
			return (-1);
		paths = command_path(ms, node->com);
		if (!paths)
			return (-1);
		return_norm = check_comand_norm(ms, node, paths);
		ft_2darr_free(paths);
		return (return_norm);
	}
	return (0);
}

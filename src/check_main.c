/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:50:34 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 17:31:56 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_cmd_error(int flag, char *error_node)
{
	if (flag > 0)
	{
		printf("minishell: %s: command not found\n", error_node);
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
	if (access(search_cmd, 0) != 0)
		flag++;
	else
	{
		free(search_cmd);
		return (0);
	}
	free(search_cmd);
	return (flag);
}

int	check_comand_norm(t_comand *node, char **paths)
{
	int		flag;
	int		i;
	char	*error_node;

	i = -1;
	while (node)
	{
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
	ft_2darr_free(paths);
	return (check_cmd_error(flag, error_node));
}

int	check_comand(t_meta *ms)
{
	char		**paths;
	t_comand	*node;

	node = ms->comand;
	if (node->com)
	{
		paths = command_path();
		return (check_comand_norm(node, paths));
	}
	return (0);
}
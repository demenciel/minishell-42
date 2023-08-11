/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:50:34 by acouture          #+#    #+#             */
/*   Updated: 2023/08/11 15:52:00 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_cmd_error(t_meta *ms, int flag, char *error_node)
{
	if (flag > 0)
	{
		print_error(ms, error_node);
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
	ft_2darr_free(paths);
	return (check_cmd_error(ms, flag, error_node));
}

int	check_comand(t_meta *ms)
{
	char		**paths;
	t_comand	*node;

	node = ms->comand;
	if (node->com)
	{
		if (ft_strncmp(".\0)", node->com[0], 2) == 0)
		{
			print_error(ms, node->com[0]);
			return (-1);
		}
		paths = command_path();
		return (check_comand_norm(ms, node, paths));
	}
	return (0);
}

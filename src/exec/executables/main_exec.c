/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:34:54 by acouture          #+#    #+#             */
/*   Updated: 2023/08/09 13:49:27 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Creates an array to store PID for each nodes
 * @param node Pointer to the nodes
 * @return The number of nodes in the list
 */
int	init_pid_and_nb_node(t_comand *node)
{
	int	nb_node;
	int	i;
	int	j;

	j = -1;
	i = 0;
	nb_node = lst_size(node);
	g()->pid = malloc(sizeof(pid_t) * (nb_node + 1));
	if (!g()->pid)
		f_all_clean_exit(mt(), MALLOC_ERROR);
	while (i < nb_node)
	{
		g()->pid[i] = j;
		i++;
		j--;
	}
	return (nb_node);
}

/**
 * @brief Executes a single node in the program
 * @param node The node to be executed
 * @param fd The fd into which to write the execution
 */
void	exec_one_node(t_comand *node, int fd, int out_fd)
{
	if (ft_check_builtins(node->com))
		find_builtins(node, out_fd);
	else
		pipex(node, false, fd, out_fd);
}

/**
 * @brief The execute function for exec_multi_node
 * @param out_fd The fd to write in
 * @param node The node containing the command to be executed
 * @param nb_node The number of nodes
 */
void	exec_nodes(int out_fd, t_comand *node, int nb_node)
{
	if (node->com == NULL || node->com[0] == NULL)
	{
		wait_free_pid(nb_node);
		return ;
	}
	if (node->next == NULL)
		exec_one_node(node, g()->in_fd, out_fd);
	else
	{
		if (!ft_check_builtins(node->com))
			pipex(node, true, g()->in_fd, out_fd);
		else
		{
			find_builtins(node, out_fd);
			close(out_fd);
		}
	}
}

/**
 * @brief Iterates over all the nodes in the program,
 * 			assigns the appropriate fd, and executes the node
 * @param node The node to be executed
 */
void	exec_multi_node(t_comand *node)
{
	int	pipe_end[2];
	int	out_fd;
	int	nb_node;

	if (!node || pipe(pipe_end) != 0)
		return ;
	nb_node = init_pid_and_nb_node(node);
	g()->in_fd = pipe_end[0];
	while (node)
	{
		out_fd = redirect_nodes(pipe_end, node);
		if (out_fd < 0)
			return ;
		else if (out_fd == HEREDOC_ERROR)
			break ;
		exec_nodes(out_fd, node, nb_node);
		node = node->next;
		g()->pid_index++;
	}
	wait_free_pid(nb_node);
}

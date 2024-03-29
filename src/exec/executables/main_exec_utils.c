/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:34:58 by acouture          #+#    #+#             */
/*   Updated: 2023/08/14 12:59:10 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Closes all of the open FD except for the STD FDS
 */
void	clean_fd(void)
{
	int	i;

	i = 2;
	while (++i < 200)
		close(i);
}

/**
 * @brief Initialize the content of the exec struct
 */
void	init_exec_struct(void)
{
	t_exec	*p;

	p = g();
	p->in_fd = 0;
	p->old_fd = 0;
	p->out_fd = 0;
	p->env_list = NULL;
	p->export_list = NULL;
	p->pid = 0;
	p->pid_index = 0;
	p->redir_flag = false;
	p->pid_flag = false;
}

/**
 * @brief Count the numbers of nodes in a given linked list
 * @param lst Linked list
 * @return The number of nodes
 */
int	lst_size(t_comand *lst)
{
	int			i;
	t_comand	*node;

	i = 0;
	node = lst;
	if (!node)
		return (0);
	while (node->next)
	{
		i++;
		node = node->next;
	}
	if (node->next == NULL)
		i++;
	return (i);
}

/**
 * @brief Executes the waitpid for each items in the PID Array
 * and closes the in_fd finally frees the array
 */
void	wait_free_pid(t_meta *ms, int nb_node)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < nb_node)
	{
		if (g()->pid)
			waitpid(g()->pid[i], &status, 0);
		close(g()->in_fd);
		i++;
		f_signal_in(status, ms);
	}
	clean_fd();
	g()->pid_index = 0;
	if (g()->pid_flag)
		free(g()->pid);
}

int	check_for_path(void)
{
	char	*path;

	path = get_env("PATH");
	if (path == NULL)
		return (-1);
	else
		free(path);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:34:54 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 17:04:08 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Creates an array to store PID for each nodes
 * @param node Pointer to the nodes
 * @return The number of nodes in the list
 */
int	init_pid_and_nb_node(t_meta *ms)
{
	int	nb_node;
	int	i;
	int	j;

	j = -1;
	i = 0;
	nb_node = lst_size(ms->comand);
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
void	exec_one_node(t_meta *ms, int fd, int out_fd)
{
	if (ft_check_builtins(ms))
		find_builtins(ms, out_fd);
	else
		pipex(ms, false, fd, out_fd);
}

/**
 * @brief The execute function for exec_multi_node
 * @param out_fd The fd to write in
 * @param node The node containing the command to be executed
 * @param nb_node The number of nodes
 */
void	exec_nodes(int out_fd, t_meta *ms)
{
	t_comand	*node;

	node = ms->comand;
	if (node->com == NULL || node->com[0] == NULL)
		return ;
	if (node->next == NULL)
		exec_one_node(ms, g()->in_fd, out_fd);
	else
	{
		if (!ft_check_builtins(ms))
			pipex(ms, true, g()->in_fd, out_fd);
		else
		{
			find_builtins(ms, out_fd);
			close(out_fd);
		}
	}
}

void	free_ms_node(t_comand *ms)
{
	if (ms->com)
		ft_free_tab_char(ms->com);
	free(ms->stin);
	free(ms->stout);
	free(ms);
}

/**
 * @brief Iterates over all the nodes in the program,
 * 			assigns the appropriate fd, and executes the node
 * @param node The node to be executed
 */
void	exec_multi_node(t_meta *ms)
{
	int			pipe_end[2];
	int			out_fd;
	int			nb_node;
	t_comand	*next_node;

	if (!ms->comand || pipe(pipe_end) != 0)
		return ;
	nb_node = init_pid_and_nb_node(ms);
	g()->in_fd = pipe_end[0];
	while (ms->comand)
	{
		out_fd = redirect_nodes(pipe_end, ms);
		if (out_fd < 0)
			return ;
		else if (out_fd == HEREDOC_ERROR)
			break ;
		exec_nodes(out_fd, ms);
		next_node = ms->comand->next;
		free_ms_node(ms->comand);
		ms->comand = next_node;
		g()->pid_index++;
	}
	wait_free_pid(ms, nb_node);
}

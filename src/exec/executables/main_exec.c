/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:34:54 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 16:14:31 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
}

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

int	redirect_nodes(int *pipe, t_meta *ms)
{
	int	out_fd;

	if (ms->comand->next == NULL)
		out_fd = 1;
	else
		out_fd = pipe[1];
	if (ms->comand->stin != NULL)
	{
		g()->in_fd = redirect_in(ms, pipe);
		if (g()->in_fd == FD_ERROR)
			return (FD_ERROR);
		else if (g()->in_fd == HEREDOC_ERROR)
			return (HEREDOC_ERROR);
	}
	if (ms->comand->stout != NULL)
	{
		out_fd = redirect_out(ms);
		if (out_fd < 0)
			return (FD_ERROR);
		g()->redir_flag = true;
	}
	return (out_fd);
}

void	wait_free_pid(t_meta *ms, int nb_node)
{
	int	i;
	int status;

	i = 0;
	status = 0;
	while (i < nb_node)
	{
		waitpid(g()->pid[i], &status, 0);
		close(g()->in_fd);
		i++;
		f_signal_in(status, ms);
	}
	clean_fd();
	g()->pid_index = 0;
	free(g()->pid);
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
		f_all_clean_exit(ms, MALLOC_ERROR);
	while (i < nb_node)
	{
		g()->pid[i] = j;
		i++;
		j--;
	}
	return (nb_node);
}

void	free_ms_node(t_comand *ms)
{
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
	int	pipe_end[2];
	int	out_fd;
	int	nb_node;
	t_comand *next_node;


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
		if (ms->comand->com == NULL || ms->comand->com[0] == NULL)
		{
			wait_free_pid(ms, nb_node);
			return ;
		}
		if (ms->comand->next == NULL)
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
		next_node = ms->comand->next;
		free_ms_node(ms->comand);
		ms->comand = next_node;
		g()->pid_index++;
	}
	wait_free_pid(ms, nb_node);
}

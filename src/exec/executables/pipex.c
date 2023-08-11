/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:31:17 by acouture          #+#    #+#             */
/*   Updated: 2023/08/11 17:05:18 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Executes a command with its absolute path.
 * @param cmd Path and command to be executed
 */
void	execute_absolute(t_meta *ms, char **cmd)
{
	if (access(ms->comand->com[0], 0) == 0)
	{
		clean_fd();
		if (execve(ms->comand->com[0], cmd, g()->env_list) != 0)
			exit(ms->exit_status);
	}
	else
		return ;
}

/**
 * @brief Creates paths to check executable commands
 */
char	**get_env_path(void)
{
	char	**path;
	bool	found;
	int		i;

	path = NULL;
	i = 0;
	while (g()->env_list[i])
	{
		if (ft_strncmp("PATH", g()->env_list[i], 4) == 0)
		{
			found = true;
			break ;
		}
		else
			found = false;
		i++;
	}
	if (found)
		path = ft_split(g()->env_list[i], ':');
	return (path);
}

/**
 * @brief By parsing the path, checks if the command exists, if yes, executes it
 * @param cmd The command to be executed
 */
void	exec_cmd(t_meta *ms, char **cmd)
{
	int		i;
	char	*search_cmd;
	char	**paths;

	i = -1;
	paths = get_env_path();
	while (paths[++i])
		paths[i] = ft_strjoin(paths[i], "/");
	i = -1;
	if (ft_strchr(cmd[0], '/'))
	{
		execute_absolute(ms, cmd);
		return ;
	}
	while (paths[++i])
	{
		search_cmd = ft_strjoin(paths[i], cmd[0]);
		if (access(search_cmd, 0) == 0)
		{
			clean_fd();
			execve(search_cmd, cmd, g()->env_list);
		}
		free(search_cmd);
	}
	ft_2darr_free(paths);
}

void	pipex_main(t_meta *ms, bool multi, int input_fd, int out_fd)
{
	int	pipe_end[2];

	if (pipe(pipe_end) != 0)
		return ;
	g()->pid[g()->pid_index] = fork();
	if (g()->pid[g()->pid_index] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close(pipe_end[0]);
		dup2(input_fd, STDIN_FILENO);
		if (!multi || g()->redir_flag)
			dup2(out_fd, STDOUT_FILENO);
		else
			dup2(pipe_end[1], STDOUT_FILENO);
		exec_cmd(ms, ms->comand->com);
		f_free_exit_child(ms, 2);
	}
	else
	{
		g()->redir_flag = false;
		close(pipe_end[1]);
		dup2(pipe_end[0], g()->in_fd);
		close(pipe_end[0]);
	}
}

/**
 * @brief Reproduce the effect of a pipe in shell ( | )
 * @param cmd The commands to be executed
 */
void	pipex(t_meta *ms, bool multi, int input_fd, int out_fd)
{
	signal(SIGINT, f_sighandler_com);
	if (check_for_path() == -1)
		return ;
	if (g()->pid[g()->pid_index] == -1 && (ms->comand->stin == NULL))
		input_fd = 0;
	pipex_main(ms, multi, input_fd, out_fd);
}

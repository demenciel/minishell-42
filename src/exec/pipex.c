

#include "../../inc/minishell.h"

char	**get_env_path(void)
{
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (g()->env_list[i])
	{
		if (ft_strncmp("PATH", g()->env_list[i], 4) == 0)
			break ;
		i++;
	}
	path = ft_split(g()->env_list[i], ':');
	return (path);
}

/**
 * @brief By parsing the path, checks if the command exists, if yes, executes it
 * @param cmd The command to be executed
*/
void	exec_cmd(char **cmd)
{
	int		i;
	int		flag;
	char	*search_cmd;
	char	**paths;

	i = -1;
	paths = get_env_path();
	while (paths[++i])
		paths[i] = ft_strjoin(paths[i], "/");
	i = -1;
	while (paths[++i])
	{
		flag = 0;
		search_cmd = ft_strjoin(paths[i], cmd[0]);
		if (access(search_cmd, 0) == 0)
		{
			execve(search_cmd, cmd, g()->env_list);
			free(search_cmd);
		}
		else
			flag++;
	}
	if (flag > 0)
		print_error(cmd[0]);
}

/**
 * @brief Opens a file to read
 * @param fd1 The file to be open
 * @return The value of fd. Returns STDOUT if no file. Returns
	-1 if error opening file
*/
int	open_rd_fd(char *fd1)
{
	int	fd;

	fd = 0;
	if (!fd1)
		return (0);
	fd = open(fd1, O_RDONLY);
	if (!fd)
		fd_error(fd1);
	return (fd);
}

/**
 * @brief Reproduce the effect of a pipe in shell ( | )
 * @param cmd The commands to be executed
*/
void	pipex(char **cmd, bool multi, int input_fd)
{
	int pipe_end[2];

	if (pipe(pipe_end) != 0)
		return ;
	if (multi)
	{
		if (fork() == 0)
		{
			close(pipe_end[0]);
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
			dup2(pipe_end[1], STDOUT_FILENO);
			close(pipe_end[1]);
			exec_cmd(cmd);
		}
		else
		{
			wait(NULL);
			close(pipe_end[1]);
			g()->in_fd = pipe_end[0];
		}
	}
	else
	{
		if (fork() == 0)
		{
			dup2(g()->in_fd, STDIN_FILENO);
			close(pipe_end[1]);
			close(pipe_end[0]);
			exec_cmd(cmd);
		}
		else
			wait(NULL);
	}
}

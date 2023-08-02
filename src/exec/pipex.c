

#include "../../inc/minishell.h"

/**
 * @brief Executes a command with its absolute path.
 * @param cmd Path and command to be executed
*/
void	execute_absolute(char **cmd)
{
	if (access(cmd[0], 0) == 0)
	{
		if (execve(cmd[0], cmd, g()->env_list) != 0)
			exit(mt()->exit_status);
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
	if (ft_strchr(cmd[0], '/'))
	{
		execute_absolute(cmd);
		return ;
	}
	while (paths[++i])
	{
		flag = 0;
		search_cmd = ft_strjoin(paths[i], cmd[0]);
		if (access(search_cmd, 0) == 0)
		{
			for (int i = 3; i < 200; i++) {
				close(i);
			}
			if (execve(search_cmd, cmd, g()->env_list) != 0)
				exit(mt()->exit_status);
		}
		else
			flag++;
		free(search_cmd);
	}
	ft_2darr_free(paths);
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
	if (fd < 0)
	{
		fd_error(fd1);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Create a file to read
 * @param fd1 The file to be open
 * @return The value of fd. Returns STDOUT if no file. Returns
	-1 if error opening file
*/
int	create_rd_fd(char *fd1)
{
	int	fd;

	fd = 0;
	if (!fd1)
		return (0);
	fd = open(fd1, O_RDWR | O_CREAT | O_TRUNC , 00644);
	if (fd < 0)
	{
		fd_error(fd1);
		return (-1);
	}
	return (fd);
}

int	append_rd_fd(char *fd1)
{
	int	fd;

	fd = 0;
	if (!fd1)
		return (0);
	fd = open(fd1, O_RDWR | O_CREAT | O_APPEND , 00644);
	if (fd < 0)
	{
		fd_error(fd1);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Reproduce the effect of a pipe in shell ( | )
 * @param cmd The commands to be executed
*/
pid_t	pipex(t_comand *node, bool multi, int input_fd, int out_fd)
{
	int 	pipe_end[2];
	int i = 0;

	if (multi)
	{
		if (pipe(pipe_end) != 0)
			return (-1);
		g()->pid[i] = fork();
		if (g()->pid[i] == 0)
		{
			close(pipe_end[0]);
			dup2(input_fd, STDIN_FILENO);
			dup2(pipe_end[1], STDOUT_FILENO);
			exec_cmd(node->com);
			for (int i = 3; i < 200; i++) {
				close(i);
			}
			exit(1);
		}
		else
		{
			close(pipe_end[1]);
			dup2(pipe_end[0], g()->in_fd);
			close(pipe_end[0]);
		}
		i++;
	}
	else
	{
		g()->pid[i] = fork();
		if (g()->pid[i] == 0)
		{
			dup2(g()->in_fd, STDIN_FILENO);
			dup2(out_fd, STDOUT_FILENO);
			exec_cmd(node->com);
			for (int i = 3; i < 200; i++) {
				close(i);
			}
			exit(1);
		}
	}
	return (0);
}

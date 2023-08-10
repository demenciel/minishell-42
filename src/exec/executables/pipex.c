

#include "../../../inc/minishell.h"

/**
 * @brief Executes a command with its absolute path.
 * @param cmd Path and command to be executed
*/
void	execute_absolute(t_meta *ms, char **cmd)
{
	if (access(cmd[0], 0) == 0)
	{
		if (execve(cmd[0], cmd, g()->env_list) != 0)
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
		execute_absolute(ms, cmd);
		return ;
	}
	while (paths[++i])
	{
		flag = 0;
		search_cmd = ft_strjoin(paths[i], cmd[0]);
		if (access(search_cmd, 0) == 0)
		{
			clean_fd();
			execve(search_cmd, cmd, g()->env_list);
		}
		else
			flag++;
		free(search_cmd);
	}
	ft_2darr_free(paths);
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
void	pipex(t_meta *ms, bool multi, int input_fd, int out_fd)
{
	int 	pipe_end[2];
	char 	*path;


	signal(SIGINT, f_sighandler_com);
	if (pipe(pipe_end) != 0)
		return ;
	path = get_env("PATH");
	if (path == NULL)
		return ;
	else
		free(path);
	if (g()->pid[g()->pid_index] == -1 && ms->comand->stin == NULL)
		input_fd = 0;
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
		clean_fd();
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

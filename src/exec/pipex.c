

#include "../../inc/minishell.h"

/**
 * @brief By parsing the path, checks if the command exists, if yes, executes it
 * @param cmd The command to be executed
*/
void	exec_cmd(char **cmd)
{
	t_pipex	*p;
	int		i;
	char	*search_cmd;
	char	**paths;

	i = -1;
	p = g();
	paths = ft_split(getenv("PATH"), ':');
	while (paths[++i])
		paths[i] = ft_strjoin(paths[i], "/");
	i = -1;
	while (paths[++i])
	{
		search_cmd = ft_strjoin(paths[i], cmd[0]);
		if (access(search_cmd, 0) == 0)
		{
			execve(search_cmd, cmd, p->env_list);
			free(search_cmd);
		}
		else
			print_error(cmd[0]);
	}
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
void	pipex(char **cmd, int n, char *infile)
{
	int pipe_end[2];
	int input;
	int i;

	i = 0;
	input = open_rd_fd(infile);
	while (i < (n - 1))
	{
		if (pipe(pipe_end) != 0)
			pipex_fail("PIPE");
		if (fork() == 0)
		{
			close(pipe_end[0]);
			dup2(input, STDIN_FILENO);
			close(input);
			dup2(pipe_end[1], STDOUT_FILENO);
			close(pipe_end[1]);
			exec_cmd(cmd);
		}
		else
		{
			wait(NULL);
			close(pipe_end[1]);
			input = pipe_end[0];
		}
		i++;
	}
	if (fork() == 0)
	{
		dup2(input, STDIN_FILENO);
		exec_cmd(cmd);
		close(input);
	}
	else
		wait(NULL);
}
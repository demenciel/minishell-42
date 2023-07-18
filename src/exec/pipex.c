

#include "../../inc/minishell.h"

/**
 * @brief By parsing the path, checks if the command exists, if yes, executes it
 * @param cmd The command to be executed
*/
void	exec_cmd(char **cmd)
{
	t_pipex	*p;
	int		i;
	int 	flag;
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
		flag = 0;
		search_cmd = ft_strjoin(paths[i], cmd[0]);
		if (access(search_cmd, 0) == 0)
		{
			execve(search_cmd, cmd, p->env_list);
			free(search_cmd);
		}
		else
			flag++;
	}
	if (flag > 0)
	{
		print_error(cmd[0]);
		exit(0);
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
void	pipex(t_comand *list, char *infile)
{
	t_comand *node;
	int pipe_end[2];
	int input;

	node = list;
	input = open_rd_fd(infile);
	while (node->next)
	{
		input = open_rd_fd(node->stin);
		if (pipe(pipe_end) != 0)
			pipex_fail("PIPE");
		if (fork() == 0)
		{
			close(pipe_end[0]);
			dup2(input, STDIN_FILENO);
			close(input);
			dup2(pipe_end[1], STDOUT_FILENO);
			close(pipe_end[1]);
			if (ft_check_builtins(node->com))
				find_builtins(node);
			else
				exec_cmd(node->com);
		}
		else
		{
			wait(NULL);
			close(pipe_end[1]);
			input = pipe_end[0];
		}
		node = node->next;
	}
	if (fork() == 0)
	{
		dup2(input, STDIN_FILENO);
		close(input);
		if (ft_check_builtins(node->com))
			find_builtins(node);
		else
			exec_cmd(node->com);
	}
	else
		wait(NULL);
}
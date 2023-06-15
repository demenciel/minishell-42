

#include "../../inc/minishell.h"

/**
 * @brief Loops readline and add each line to rl history until limiter is found
 * @param limiter The limiter for the heredocs
*/
void	heredocs(char *limiter)
{
	char	*rl_line;

	while (1)
	{
		rl_line = readline("heredoc> ");
		add_history(rl_line);
		if (ft_strnstr(rl_line, limiter, ft_strlen(rl_line)))
			break ;
		free(rl_line);
	}
}

/**
 * @brief Redirects the infile to the STDIN
 * @param cmd Command to be executed
 * @param infile The infile to become the STDIN
*/
void	redir_in(char *cmd, char *infile)
{
	int	fd;
	int	stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	fd = open_rd_fd(infile);
	if (fd == -1)
		print_error("Error opening fd");
	dup2(fd, STDIN_FILENO);
	close(fd);
	exec_cmd(cmd);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
}

/**
 * @brief Redirects the output of the command executed,
	but appends the ouput to the infile
 * @param cmd The command to be executed
 * @param infile If there is a fd, redirects it as the input of the command
 * @param outfile The result of the appended file
*/
void	append_out(char *cmd, char *infile, char *outfile)
{
	int	fd[2];
	int	stdout_backup;

	stdout_backup = dup(STDOUT_FILENO);
	fd[0] = open_rd_fd(infile);
	if (fd[0] == -1)
		print_error("Error opening fd");
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	fd[1] = open(outfile, O_RDWR | O_APPEND | O_CREAT, 00644);
	if (fd[1] < 0)
		fd_error(outfile);
	dup2(fd[1], STDOUT_FILENO);
	exec_cmd(cmd);
	close(fd[1]);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
}

/**
 * @brief Redirects the output of the command executed
 * @param cmd The command to be executed
 * @param infile If there is a fd, redirects it as the input of the command
 * @param outfile The new file created as the output of the executed command
*/
void	redir_out(char *cmd, char *infile, char *outfile)
{
	int	fd[2];
	int	stdout_backup;

	stdout_backup = dup(STDOUT_FILENO);
	fd[0] = open_rd_fd(infile);
	if (fd[0] == -1)
		print_error("Error opening fd");
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	fd[1] = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (fd[1] < 0)
		fd_error(outfile);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		print_error("Dup2 failed");
	exec_cmd(cmd);
	close(fd[1]);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		print_error("Dup2 failed");
	close(stdout_backup);
}

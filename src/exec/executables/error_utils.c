/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 07:42:16 by acouture          #+#    #+#             */
/*   Updated: 2023/08/11 16:58:23 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Function to print an error if the command is not found
*/
void	print_error(t_meta *ms, char *cmd)
{
	if (!cmd)
		return ;
	write(2, "minishell: ", 12);
	perror(cmd);
	ms->exit_status = errno;
	ms->error_flag = 1;
}

/**
 * @brief Function to print an error if the input of export is not valid
*/
void	export_error(t_meta *ms, char *id)
{
	write(2, "minishell: ", 12);
	perror(id);
	ms->exit_status = errno;
	ms->error_flag = 1;
}

/**
 * @brief Function to print an error if file or directory is inexistent
*/
void	cd_error(t_meta *ms, char *input)
{
	write(2, "minishell: cd: ", 16);
	perror(input);
	ms->exit_status = errno;
	ms->error_flag = 1;
}

/**
 * @brief Function to print an error if the command is not found
*/
void	fd_error(t_meta *ms, char *fd)
{
	write(2, "minishell: ", 12);
	perror(fd);
	ms->exit_status = errno;
	ms->error_flag = 1;
}

/**
 * @brief Function to print an error if the command is not found
*/
void	pipex_fail(t_meta *ms, char *s)
{
	write(2, "minishell: ", 12);
	perror(s);
	ms->exit_status = errno;
	ms->error_flag = 1;
}

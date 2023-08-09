/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 07:42:16 by acouture          #+#    #+#             */
/*   Updated: 2023/08/09 09:28:16 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(char *cmd)
{
	if (!cmd)
		return ;
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 29);
	mt()->exit_status = 1;
	mt()->error_flag = 1;
}

void	export_error(char *id)
{
	write(2, "minishell: ", 16);
	write(2, id, ft_strlen(id));
	write(2, ": not a valid identifier\n", 29);
	mt()->exit_status = 1;
	mt()->error_flag = 1;
}

void	cd_error(char *input)
{
	write(2, "minishell: cd: ", 16);
	write(2, input, ft_strlen(input));
	write(2, ": no such file or directory\n", 29);
	mt()->exit_status = 1;
	mt()->error_flag = 1;
}

void	fd_error(char *fd)
{
	write(2, "minishell: ", 12);
	write(2, fd, ft_strlen(fd));
	write(2, ": no such file or directory\n", 29);
	mt()->exit_status = 1;
	mt()->error_flag = 1;
}

void	pipex_fail(char *s)
{
	perror(s);
	exit(1);
}

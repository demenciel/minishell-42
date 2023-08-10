/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 07:42:16 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 17:06:43 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	print_error(t_meta *ms, char *cmd)
{
	if (!cmd)
		return ;
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 29);
	ms->exit_status = 1;
	ms->error_flag = 1;
}

void	export_error(t_meta *ms, char *id)
{
	write(2, "minishell: ", 16);
	write(2, id, ft_strlen(id));
	write(2, ": not a valid identifier\n", 29);
	ms->exit_status = 1;
	ms->error_flag = 1;
}

void	cd_error(t_meta *ms, char *input)
{
	write(2, "minishell: cd: ", 16);
	write(2, input, ft_strlen(input));
	write(2, ": no such file or directory\n", 29);
	ms->exit_status = 1;
	ms->error_flag = 1;
}

void	fd_error(t_meta *ms, char *fd)
{
	write(2, "minishell: ", 12);
	write(2, fd, ft_strlen(fd));
	write(2, ": no such file or directory\n", 29);
	ms->exit_status = 1;
	ms->error_flag = 1;
}

void	pipex_fail(t_meta *ms, char *s)
{
	write(2, "minishell: ", 12);
	write(2, s, ft_strlen(s));
	write(2, ": pipe failed\n", 29);
	ms->exit_status = 1;
	ms->error_flag = 1;
}

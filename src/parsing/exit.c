/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:02:33 by rofontai          #+#    #+#             */
/*   Updated: 2023/08/10 19:02:55 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_exit(t_meta *ms, int fd)
{
	int	i;
	int	nb;

	i = 0;
	if (ft_strcmp(ms->comand->com[0], "exit") == 0)
	{
		i = f_size_table(ms->comand->com);
		if (i > 2)
		{
			f_message_short(fd);
			ms->exit_status = 1;
			return (0);
		}
		else if (i == 2 && f_arg_is_num(ms->comand->com[1]) == -1)
			f_message(ms, ms->comand->com[1], fd);
		else if (i == 2)
		{
			nb = ft_atoi(ms->comand->com[1]);
			if (nb > 256)
				nb = nb % 256;
			f_all_clean_exit(ms, nb);
		}
		f_all_clean(ms, NULL);
	}
	return (0);
}

int	f_size_table(char **table)
{
	int	i;

	i = 0;
	if (!table || *table == NULL)
		return (i);
	while (table[i])
		i++;
	return (i);
}

int	f_arg_is_num(char *txt)
{
	int	i;

	i = 0;
	while (txt[i])
	{
		if (ft_isalpha(txt[i]) == 1)
			return (-1);
		i++;
	}
	return (0);
}

void	f_message(t_meta *ms, char *txt, int fd)
{
	ft_putendl_fd("exit", fd);
	ft_putstr_fd("exit: ", fd);
	ft_putstr_fd(txt, fd);
	f_all_clean(ms, ": numeric argument required");
}

void	f_message_short(int fd)
{
	ft_putendl_fd("exit", fd);
	ft_putendl_fd("exit: too many arguments", fd);
}

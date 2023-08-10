/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 07:42:47 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 12:54:06 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief This function is for the echo flags
 */
char	*ft_strtrim_echo(char const *s1, char const *set)
{
	char	*new_str;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) + 1;
	while (s1[start] == *set)
		start++;
	new_str = (char *)malloc((end - start) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1 + start, ((end - start) + 1));
	return (new_str);
}

int	iterate_over_echo_flag(t_meta *ms, int i)
{
	t_comand	*temp;
	char		*trim;
	int			j;

	j = i;
	temp = ms->comand;
	trim = NULL;
	while (temp->com[j])
	{
		trim = ft_strtrim_echo(temp->com[j], "-");
		if (!(ft_strchr(trim, '-')))
		{
			if (ft_strcmp("n", trim) == 0)
				i++;
			else
				break ;
		}
		j++;
	}
	free(trim);
	return (i);
}

void	print_echo_string(int i, t_meta *ms, int flag, int input_fd)
{
	char	*echo_string;
	int		len_com;

	echo_string = NULL;
	len_com = i;
	while (ms->comand->com[len_com])
		len_com++;
	while (ms->comand->com[i])
	{
		if (ft_strncmp(ms->comand->com[1], "-n", ft_strlen(ms->comand->com[1])) == 0
			&& !ms->comand->com[2])
			break ;
		if (i == (len_com - 1))
			echo_string = ft_strdup(ms->comand->com[i]);
		else
			echo_string = ft_strjoin(ms->comand->com[i], " ");
		ft_echo(echo_string, input_fd);
		free(echo_string);
		i++;
	}
	if (!(flag > 0))
		ft_putchar_fd('\n', input_fd);
}

int	check_echo_args(t_meta *ms, int input_fd)
{
	if (!ms->comand->com[1])
	{
		ft_putchar_fd('\n', input_fd);
		return (-1);
	}
	return (0);
}

/**
 * @brief Checks the content of the node,
	and executes the builtin depending of the content of the node
*/
void	find_echo(t_meta *ms, int input_fd)
{
	int		i;
	int		flag;
	char	*trim;

	i = 1;
	flag = 0;
	if (ft_strcmp(ms->comand->com[0], "echo") == 0)
	{
		if (check_echo_args(ms, input_fd) == -1)
			return ;
		if (ft_strcmp("-n", ms->comand->com[1]) == 0)
		{
			trim = ft_strtrim_echo(ms->comand->com[1], "-");
			if (!(ft_strchr(trim, '-')))
			{
				i = 2;
				i = iterate_over_echo_flag(ms, i);
				flag = 1;
			}
			free(trim);
		}
		print_echo_string(i, ms, flag, input_fd);
	}
}

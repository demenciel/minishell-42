/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:29:08 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 17:32:19 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_path(char *s1, char *s2)
{
	char			*join_str;
	unsigned int	i;
	unsigned int	j;

	i = -1;
	j = 0;
	if ((!s1 && s2) || s1 == NULL)
		return ((char *)s2);
	join_str = malloc(((ft_strlen(s1) + 1) + ft_strlen(s2)) * sizeof(char));
	if (!join_str)
		return (NULL);
	while (s1[++i])
		join_str[i] = s1[i];
	free(s1);
	while (s2[j])
		join_str[i++] = s2[j++];
	join_str[i] = '\0';
	return (join_str);
}

int	check_absolute_path(char **cmd)
{
	if (access(cmd[0], 0) == 0)
		return (0);
	else
		return (-1);
	return (0);
}

char	**command_path(void)
{
	char	**paths;
	int		i;

	i = -1;
	paths = NULL;
	paths = get_env_path();
	if (!paths)
		return (paths);
	while (paths[++i])
		paths[i] = ft_strjoin_path(paths[i], "/");
	return (paths);
}

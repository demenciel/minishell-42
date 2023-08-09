/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:38:33 by acouture          #+#    #+#             */
/*   Updated: 2023/08/09 09:43:27 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**

	* @brief Mimics the unset builtin in bash. Finds a variable in the export list and deletes it from the environment
 * @param var The variable to delete
*/
void	ft_unset_env(char *var)
{
	int		i;
	int		j;
	t_exec	*p;

	i = 0;
	j = 0;
	p = g();
	while (p->env_list[i])
	{
		if (ft_strncmp(var, p->env_list[i], ft_strlen(var)) == 0)
		{
			free(p->env_list[i]);
			j = i;
			while (p->env_list[j])
			{
				p->env_list[j] = p->env_list[j + 1];
				j++;
			}
			p->env_list = ft_realloc(p->env_list, j * sizeof(char *), (j + 1)
				* sizeof(char *));
			break ;
		}
		i++;
	}
}

/**

	* @brief Mimics the unset builtin in bash. Finds a variable in the environment and deletes it from the environment
 * @param var The variable to delete
*/
void	ft_unset_export(char *var)
{
	int		i;
	int		j;
	char	*trimmed;
	char	set[12];

	set[12] = "declare -x ";
	i = 0;
	j = 0;
	if (g()->export_list == NULL)
		return ;
	while (g()->export_list[i])
	{
		while (set[j] == g()->export_list[i][j])
			j++;
		trimmed = ft_strdup(&g()->export_list[i][j]);
		if (ft_strncmp(var, trimmed, ft_strlen(var)) == 0)
		{
			free(g()->export_list[i]);
			j = i;
			while (g()->export_list[j])
			{
				g()->export_list[j] = g()->export_list[j + 1];
				j++;
			}
			g()->export_list = ft_realloc(g()->export_list, j * sizeof(char *),
				(j + 1) * sizeof(char *));
			free(trimmed);
			break ;
		}
		free(trimmed);
		i++;
	}
}

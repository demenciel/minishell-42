/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 08:45:59 by acouture          #+#    #+#             */
/*   Updated: 2023/08/11 17:01:31 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Goes at index position in the list and change its content by var
 * @param var the new content of the var
 * @param index The position of the list in which to change the content
 */
void	change_var_content_export(char *var, int index)
{
	char	*new_var_content;
	char	*new_var;

	if (ft_strchr(var, '='))
	{
		new_var = ft_strdup(var);
		new_var_content = ft_strjoin("declare -x ", new_var);
		free(new_var);
	}
	else
		new_var_content = ft_strjoin("declare -x ", var);
	free(g()->export_list[index]);
	g()->export_list[index] = new_var_content;
}

/**
 * @brief Before adding the new_var to the export, checks if it is already
 * in the list. If it is, replaces the content of its original
 * @param new_var
 */
int	add_var_to_export_check(char *new_var)
{
	int	i_double;

	i_double = 0;
	if (checks_for_doubles_export(new_var) > 0)
	{
		i_double = checks_for_doubles_export(new_var);
		change_var_content_export(new_var, i_double);
		return (1);
	}
	return (0);
}

/**
 * @brief Adds the new variables inside the export list.
 * @param new_var The new variables to insert
 * @param i The index of where we currently are inside the export list
 */
void	add_var_to_export(char *new_var, int i, int *list_size)
{
	t_exec	*p;
	int		og_size;
	char	*var;

	p = g();
	og_size = *list_size;
	if (add_var_to_export_check(new_var) == 1)
		return ;
	(*list_size)++;
	p->export_list = ft_realloc(p->export_list, og_size * sizeof(char *),
			*list_size * sizeof(char *));
	if (ft_strchr(new_var, '='))
		p->export_list[i] = ft_strjoin("declare -x ", var);
	else
		p->export_list[i] = ft_strjoin("declare -x ", new_var);
	i++;
	og_size = *list_size;
	(*list_size)++;
	p->export_list = ft_realloc(p->export_list, og_size * sizeof(char *),
			*list_size * sizeof(char *));
	p->export_list[i] = NULL;
}

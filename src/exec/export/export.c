/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 08:40:57 by acouture          #+#    #+#             */
/*   Updated: 2023/08/09 09:36:06 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	checks_for_doubles_export_norm(char *set, char *check_var)
{
	int		str;
	int		j;
	char	*trimmed;

	str = 0;
	while (str < g()->export_length)
	{
		j = 0;
		while (set[j] == g()->export_list[str][j])
			j++;
		trimmed = ft_strdup(&g()->export_list[str][j]);
		if (ft_strncmp(check_var, trimmed, ft_strlen(check_var)) == 0)
		{
			free(trimmed);
			return (str);
		}
		free(trimmed);
		str++;
	}
	return (0);
}

/**
 * @brief Iterates over the export list and checks
			if var has a double in the list
 * @param var The var to compare to the list
 * @return The position in the export list
 */
int	checks_for_doubles_export(char *var)
{
	int		pos;
	char	*check_var;
	char	**var_tab;
	char	*set;

	check_var = NULL;
	set = ft_strdup("declare -x ");
	if (ft_strchr(var, '='))
	{
		var_tab = ft_split(var, '=');
		check_var = ft_strdup(var_tab[0]);
		ft_2darr_free(var_tab);
	}
	else
		check_var = ft_strdup(var);
	pos = checks_for_doubles_export_norm(set, check_var);
	free(check_var);
	free(set);
	return (pos);
}

/**
 * @brief Checks if the export list is empty. If yes, makes a copy of the env
 */
int	cpy_env_if_null(void)
{
	t_exec	*p;
	int		i;
	int		list_size;

	i = 0;
	list_size = 0;
	p = g();
	while (p->env_list[list_size])
		list_size++;
	p->env_length = list_size;
	p->export_list = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (!p->export_list)
		return (0);
	i = 0;
	while (p->env_list[i])
	{
		p->export_list[i] = ft_strjoin("declare -x ", p->env_list[i]);
		i++;
	}
	p->export_list[i] = NULL;
	return (i);
}

bool	if_var_empty(char *new_var, int *list_size, int input_fd)
{
	if (!new_var || *new_var == '\0')
	{
		order_export(list_size);
		ft_2darr_print(g()->export_list, input_fd);
		return (true);
	}
	return (false);
}

/**
 * @brief Adds an element to the env list. Simulates what (export) cmd does
 * @param new_var New element to add to list
 */
void	ft_export(char *new_var, int input_fd)
{
	int	i;
	int	list_size;

	if (check_var(new_var) == -1)
		return ;
	if (g()->export_list == NULL)
	{
		i = cpy_env_if_null();
		list_size = g()->env_length;
	}
	else
		list_size = ft_2darr_len(g()->export_list);
	if (if_var_empty(new_var, &list_size, input_fd))
		return ;
	g()->export_list = ft_cpy_export(g()->export_list);
	g()->env_list = ft_cpy_env(g()->env_list);
	if (ft_strchr(new_var, '='))
	{
		i = g()->env_length;
		add_var_to_env(new_var, i);
	}
	i = g()->export_length;
	add_var_to_export(new_var, i, &list_size);
	order_export(&list_size);
}

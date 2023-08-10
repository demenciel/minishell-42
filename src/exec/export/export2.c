/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 08:41:13 by acouture          #+#    #+#             */
/*   Updated: 2023/08/10 17:11:23 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Checks for the first value of the variable. If is not a letter
	 or underscore exits program
 * @param var Var to check
*/
int	check_var(t_meta *ms, char *var)
{
	int	i;

	i = 0;
	if (*var == '\0')
		return (-2);
	while (var[i])
	{
		if (ft_isdigit(var[0]) || ((var[i] != '/') && !(var[i] == 95)
				&& !(ft_isalpha(var[i])) && var[i] != '=') || (ft_strncmp("=",
					var, ft_strlen(var)) == 0) || (var[0] == '=' && var[1]))
		{
			export_error(ms, var);
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Swaps the two characters passed
 */
void	ft_swap_char(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief Using bubble sort, sorts the export list in ascending order
 * @param size The size of the list to sort
 */
void	order_export(int *size)
{
	int	j;
	int	swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		j = 0;
		while (j < ((*size) - 2))
		{
			if (ft_strcmp(g()->export_list[j], g()->export_list[j + 1]) > 0)
			{
				ft_swap_char(&g()->export_list[j], &g()->export_list[j + 1]);
				swap++;
			}
			j++;
		}
	}
}

/**
 * @brief This function is to make a copy of the export list
 * @param list export list to copy
 * @return Returns a copy of the list after freeing the initial list
 */
char	**ft_cpy_export(char **list)
{
	int		i;
	char	**result;

	i = 0;
	while (list[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (list[i])
	{
		result[i] = ft_strdup(list[i]);
		i++;
	}
	result[i] = NULL;
	g()->export_length = i;
	ft_2darr_free(list);
	return (result);
}

/**
 * @brief If the new element is assigning a VAR, puts the content of VAR in ("")
 * @param var The new element to check
 * @return The newly form var
 */
char	*detect_var_export(char *var)
{
	int		i;
	int		j;
	char	*new_var;

	i = 0;
	j = 0;
	new_var = malloc(ft_strlen(var) + 4);
	if (!new_var)
		return (NULL);
	while (var[i])
	{
		new_var[j] = var[i];
		if (var[i] == '=')
		{
			j++;
			new_var[j] = 34;
		}
		i++;
		j++;
	}
	new_var[j] = 34;
	new_var[j + 1] = '\0';
	return (new_var);
}

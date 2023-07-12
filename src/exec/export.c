#include "../../inc/minishell.h"
#include <strings.h>

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
	free(var);
	return (new_var);
}

/**
 * @brief Adds the new variables inside the export list.
 * @param new_var The new variables to insert
 * @param i The index of where we currently are inside the export list
*/
void	add_var_to_export(char **new_var, int i, int *list_size)
{
	int	j;
	int	og_size;

	j = 0;
	og_size = *list_size;
	while (new_var[j])
	{
		if (ft_strchr(new_var[j], '='))
			new_var[j] = detect_var_export(new_var[j]);
		(*list_size)++;
		g()->export_list = ft_realloc(g()->export_list,
										og_size * sizeof(char *),
										*list_size * sizeof(char *));
		g()->export_list[i] = ft_strjoin("declare -x ", new_var[j]);
		i++;
		j++;
		og_size = *list_size;
	}
	(*list_size)++;
	g()->export_list = ft_realloc(g()->export_list, og_size * sizeof(char *),
			*list_size * sizeof(char *));
	g()->export_list[i] = NULL;
}

/**
 * @brief Adds the new variables inside the env.
 * @param new_var The new variables to insert
 * @param i The index of where we currently are inside the env list
*/
void	add_var_to_env(char **new_var, int i)
{
	int	j;
	int	og_size;
	int	new_size;

	j = 0;
	og_size = g()->env_length;
	new_size = g()->env_length;
	while (new_var[j])
	{
		new_size++;
		g()->env_list = ft_realloc(g()->env_list, og_size * sizeof(char *),
				new_size * sizeof(char *));
		g()->env_list[i] = ft_strdup(new_var[j]);
		i++;
		j++;
		og_size = new_size;
	}
	new_size++;
	g()->env_list = ft_realloc(g()->env_list, og_size * sizeof(char *), new_size
			* sizeof(char *));
	g()->env_list[i] = NULL;
	g()->env_length = new_size;
}

/**
 * @brief Adds an element to the env list. Simulates what (export) cmd does
 * @param new_var New element to add to list
*/
void	ft_export(char *new_var)
{
	int i;
	int list_size;
	char **new_var_tab;

	check_var(new_var);
	if (!new_var || *new_var == '\0')
	{
		ft_2darr_print(g()->export_list);
		return ;
	}
	list_size = 0;
	while (g()->env_list[list_size])
		list_size++;
	g()->env_length = list_size;
	g()->export_list = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (!g()->export_list)
		return ;
	i = 0;
	while (g()->env_list[i])
	{
		g()->export_list[i] = ft_strjoin("declare -x ", g()->env_list[i]);
		i++;
	}
	g()->export_list[i] = NULL;
	new_var_tab = ft_split(new_var, ' ');
	if (ft_strchr(new_var, '='))
		add_var_to_env(new_var_tab, i);
	add_var_to_export(new_var_tab, i, &list_size);
	order_export(&list_size);
	ft_2darr_free(new_var_tab);
}
#include "../../inc/minishell.h"

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

/**
 * @brief Goes at index position in the list and change its content by var
 * @param var the new content of the var
 * @param index The position of the list in which to change the content
*/
void	change_var_content_export(char *var, int index)
{
	char *new_var_content;
	char *new_var;

	if (ft_strchr(var, '='))
	{
		new_var = ft_strdup(var);
		new_var_content = ft_strjoin("declare -x ", new_var);
		free(new_var);
	}
	else 
		new_var_content = ft_strjoin("declare -x ", var);
	g()->export_list[index] = NULL;
	free(g()->export_list[index]);
	g()->export_list[index] = new_var_content;
}


/**
 * @brief Iterates over the export list and checks if var has a double in the list
 * @param var The var to compare to the list
 * @return The position in the export list
*/
int checks_for_doubles_export(char *var)
{
	int str;
	int j;
	char *trimmed;
	char *check_var = NULL;
	char **var_tab;
	char set[12] = "declare -x ";

	str = 0;
	if (ft_strchr(var, '='))
	{
		var_tab = ft_split(var, '=');
		check_var = ft_strdup(var_tab[0]);
		ft_2darr_free(var_tab);
	}
	else
		check_var = ft_strdup(var);
	while (str < g()->export_length)
	{
		j = 0;
		while (set[j] == g()->export_list[str][j])
			j++;
		trimmed = ft_strdup(&g()->export_list[str][j]);
		if (ft_strncmp(check_var, trimmed, ft_strlen(check_var)) == 0)
		{
			free(trimmed);
			free(check_var);
			return (str) ;
		}
		free(trimmed);
		str++;
	}
	free(check_var);
	return (0);
}

/**
 * @brief Adds the new variables inside the export list.
 * @param new_var The new variables to insert
 * @param i The index of where we currently are inside the export list
*/
void	add_var_to_export(char *new_var, int i, int *list_size)
{
	int i_double;
	int	og_size;
	char *var;

	og_size = *list_size;
	if (checks_for_doubles_export(new_var) > 0)
	{
		i_double = checks_for_doubles_export(new_var);
		change_var_content_export(new_var, i_double);
		return ;
	}
	(*list_size)++;
	g()->export_list = ft_realloc(g()->export_list,
									og_size * sizeof(char *),
									*list_size * sizeof(char *));
	if (ft_strchr(new_var, '='))
	{
		var = detect_var_export(new_var);
		g()->export_list[i] = ft_strjoin("declare -x ", var);
		free(var);
	}
	else
		g()->export_list[i] = ft_strjoin("declare -x ", new_var);
	i++;
	og_size = *list_size;
	(*list_size)++;
	g()->export_list = ft_realloc(g()->export_list, og_size * sizeof(char *),
			*list_size * sizeof(char *));
	g()->export_list[i] = NULL;
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
 * @brief Checks if the export list is empty. If yes, makes a copy of the env
*/
int cpy_env_if_null(void)
{
	int i;
	int list_size;

	i = 0;
	list_size = 0;
	while (g()->env_list[list_size])
		list_size++;
	g()->env_length = list_size;
	g()->export_list = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (!g()->export_list)
		return (0); // SHOULD RETURN EXIT
	i = 0;
	while (g()->env_list[i])
	{
		g()->export_list[i] = ft_strjoin("declare -x ", g()->env_list[i]);
		i++;
	}
	g()->export_list[i] = NULL;
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
	int i;
	int list_size;

	check_var(new_var);
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
#include "../../inc/minishell.h"

/**
 * @brief Goes at index position in the list and change its content by var
 * @param var the new content of the var
 * @param index The position of the list in which to change the content
*/
void	change_var_content_env(char *var, int index)
{
	free(g()->env_list[index]);
	g()->env_list[index] = ft_strdup(var);
}

/**
 * @brief Iterates over the env list and checks if var has a double in the list
 * @param var The var to compare to the list
 * @return The position in the env list
*/
int	checks_for_doubles_env(char *var)
{
	int		str;
	int		j;
	char	*check_var;
	char	**var_tab;

	check_var = NULL;
	str = 0;
	j = 0;
	var_tab = ft_split(var, '=');
	check_var = ft_strdup(var_tab[0]);
	ft_2darr_free(var_tab);
	while (str < g()->env_length)
	{
		if (ft_strncmp(check_var, g()->env_list[str],
				ft_strlen(check_var)) == 0)
		{
			free(check_var);
			return (str);
		}
		str++;
	}
	free(check_var);
	return (0);
}

/**
 * @brief Adds the new variables inside the env.
 * @param new_var The new variables to insert
 * @param i The index of where we currently are inside the env list
*/
void	add_var_to_env(char *new_var, int i)
{
	int	i_double;
	int	og_size;
	int	new_size;

	if (checks_for_doubles_env(new_var) > 0)
	{
		i_double = checks_for_doubles_env(new_var);
		change_var_content_env(new_var, i_double);
		return ;
	}
	og_size = g()->env_length;
	new_size = og_size;
	new_size++;
	g()->env_list = ft_realloc(g()->env_list, og_size * sizeof(char *), new_size
			* sizeof(char *));
	g()->env_list[i] = ft_strdup(new_var);
	i++;
	og_size = new_size;
	new_size++;
	g()->env_list = ft_realloc(g()->env_list, og_size * sizeof(char *), new_size
			* sizeof(char *));
	g()->env_list[i] = NULL;
	g()->env_length = new_size;
}

/**
 * @brief This function is to make a copy of the env list
 * @param list export list to copy
 * @return Returns a copy of the list after freeing the initial list
*/
char	**ft_cpy_env(char **list)
{
	int i;
	char **result;

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
	result[i] = ft_strdup(list[i]);
	g()->env_length = i;
	ft_2darr_free(list);
	return (result);
}

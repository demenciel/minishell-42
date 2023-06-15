
#include "../../inc/minishell.h"
#include <strings.h>

/**
 * @brief If the new element is assigning a VAR, puts the content of VAR in ("")
 * @param var The new element to check
*/
char *detect_var_export(char *var)
{
	int i;
	int j;
	char *new_var;

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
 * @brief Adds the new variables inside the export list.
 * @param new_var The new variables to insert
 * @param i The index of where we currently are inside the export list
*/
void add_var_to_export(char **new_var, int i, int *list_size)
{
    int j;
    int og_size;

    j = 0;
    og_size = *list_size;
    while (new_var[j])
    {
        if (ft_strchr(new_var[j], '='))
            new_var[j] = detect_var_export(new_var[j]);
        (*list_size)++;
        call_struct()->export_list = ft_realloc(call_struct()->export_list, og_size * sizeof(char *), *list_size * sizeof(char *));
        call_struct()->export_list[i] = ft_strjoin("declare -x ", new_var[j]);
        i++;
        j++;
        og_size = *list_size;
    }
    (*list_size)++;
	call_struct()->export_list = ft_realloc(call_struct()->export_list, og_size * sizeof(char *), *list_size * sizeof(char *));
    call_struct()->export_list[i] = NULL;
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

	list_size = 0;
	while (call_struct()->env_list[list_size])
		list_size++;
	call_struct()->export_list = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (!call_struct()->export_list)
		return ;
	i = 0;
	while (call_struct()->env_list[i])
	{
		call_struct()->export_list[i] = ft_strjoin("declare -x ", call_struct()->env_list[i]);
		i++;
	}
	call_struct()->export_list[i] = NULL;
	if (!new_var || *new_var == '\0')
    {
    	print_tab2d(call_struct()->export_list);
        return ;
    }
	new_var_tab = ft_split(new_var, ' ');
	add_var_to_export(new_var_tab, i, &list_size);
	ft_free2darr(new_var_tab);
}

void	ft_unset(char *var)
{
	int i;
	int j;
	char *trimmed;

	i = 0;
	while (call_struct()->export_list[i])
	{
		trimmed = ft_strtrim(call_struct()->export_list[i], "declare -x ");
		if (ft_strncmp(trimmed, var, ft_strlen(var)) == 0)
		{
			free(call_struct()->export_list[i]);
			j = i;
			while (call_struct()->export_list[j])
			{
				call_struct()->export_list[j] = call_struct()->export_list[j + 1];
				j++;
			}
			call_struct()->export_list = ft_realloc(call_struct()->export_list, j * sizeof(char *), (j - 1) * sizeof(char *));
			break ;
		}
		i++;
	}
}

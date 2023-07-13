
#include "../../inc/minishell.h"
#include <strings.h>

/**
 * @brief Mimics the unset builtin in bash. Finds a variable in the environment and deletes it from the environment
 * @param var The variable to delete
*/
void	ft_unset(char *var)
{
	int i;
	int j;
	char *trimmed;

	i = 0;
	if (*var == '\0')
		return ;
	while (g()->export_list[i])
	{
		trimmed = ft_strtrim(g()->export_list[i], "declare -x ");
		if (ft_strncmp(trimmed, var, ft_strlen(var)) == 0)
		{
			free(g()->export_list[i]);
			j = i;
			while (g()->export_list[j])
			{
				g()->export_list[j] = g()->export_list[j + 1];
				j++;
			}
			g()->export_list = ft_realloc(g()->export_list, j * sizeof(char *), (j + 1) * sizeof(char *));
			free(trimmed);
			break ;
		}
		free(trimmed);
		i++;
	}
}

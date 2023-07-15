
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
	char set[12] = "declare -x ";

	i = 0;
	j = 0;
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
			g()->export_list = ft_realloc(g()->export_list, j * sizeof(char *), (j + 1) * sizeof(char *));
			free(trimmed);
			break ;
		}
		free(trimmed);
		i++;
	}
}

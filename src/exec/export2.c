#include "../../inc/minishell.h"
#include <strings.h>

/**

	* @brief Checks for the first value of the variable. If is not a letter or udnerscore exits program
 * @param var Variable to check
*/
void	check_var(char *var)
{
	int	i;

	i = 0;
	if (*var == '\0')
		return ;
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && var[i] != 95 && var[i] != '=')
			exit(1);
		i++;
	}
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
	int j;
	int swap;

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
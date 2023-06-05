
#include "../inc/minishell.h"

void f_check_arg(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		printf("Not need an argument\n");
		exit (EXIT_FAILURE);
	}
}


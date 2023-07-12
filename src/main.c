
#include "../inc/minishell.h"

int	main(int ac, char **av)
{
	t_meta *ms;

	f_check_arg(ac, av);
	ms = f_init_meta();
	while (42)
	{
		ms->line = readline("minishell > ");
		printf("\n=%s=\n\n", ms->line);
		f_check_line(ms);
		printf("\n");
		f_print_lst(ms->list);
		printf("\n");
		f_split_pipes(ms);
		printf("\n");
		// printf("com_temp =%s=", ms->com_temp);
		printf("\n");
		// f_print_lst_final(ms->comand);
		f_zero_list(ms);
		add_history(ms->line);
		if (ft_strncmp(ms->line, "exit", 4) == 0)
			break ;
	}
	f_all_clean(ms, NULL);
	return (0);
}
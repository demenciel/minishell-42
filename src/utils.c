
#include "../inc/minishell.h"

// void	f_split_line(char *line, t_meta *ms)
// {
// 	char **temp;
// 	int i;

// 	i = 0;
// 	temp = ft_split(line, 32);
// 	while (temp[i])
// 	{
// 		f_addback_node(&ms->list, f_new_node(temp[i]));
// 		i++;
// 	}
// 	free(temp);
// }


void f_zero_list(t_meta *ms)
{
	if (ms->list)
	{
		free(ms->list);
		ms->list = NULL;
	}
}

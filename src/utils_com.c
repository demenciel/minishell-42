
#include "../inc/minishell.h"

void	f_add_com(t_meta *ms, char *add)
{
	char *temp;

	temp = ft_strdup(add);
	if (ms->com_temp == NULL)
	{
		ms->com_temp = ft_strdup(temp);
		free(temp);
		temp = NULL;
	}
	else
	{
		ms->com_temp = ft_strjoin(ms->com_temp, " ");
		ms->com_temp = ft_strjoin(ms->com_temp, temp);
		free(temp);
		temp = NULL;
	}
}

void	f_add_in(t_meta *ms, char *add)
{
	char *temp;

	temp = ft_strdup(add);
	if (ms->in == NULL)
	{
		ms->in = ft_strdup(temp);
		free(temp);
		temp = NULL;
	}
	else
	{
		ms->in = ft_strjoin(ms->in, " ");
		ms->in = ft_strjoin(ms->in, temp);
		free(temp);
		temp = NULL;
	}
}

void	f_add_out(t_meta *ms, char *add)
{
	char *temp;

	temp = ft_strdup(add);
	if (ms->out == NULL)
	{
		ms->out = ft_strdup(temp);
		free(temp);
		temp = NULL;
	}
	else
	{
		ms->out = ft_strjoin(ms->out, " ");
		ms->out = ft_strjoin(ms->out, temp);
		free(temp);
		temp = NULL;
	}
}

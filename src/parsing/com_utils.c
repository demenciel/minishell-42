#include "../../inc/minishell.h"

void	f_add_com(t_meta *ms, char *add)
{
	char	*temp;
	char	*prov;

	temp = ft_strdup(add);
	if (ms->com_temp == NULL)
	{
		ms->com_temp = ft_strdup(temp);
		temp = f_freenull(temp);
	}
	else
	{
		prov = ms->com_temp;
		ms->com_temp = f_join_char(prov, 29);
		prov = f_freenull(prov);
		prov = ms->com_temp;
		ms->com_temp = ft_strjoin(prov, temp);
		prov = f_freenull(prov);
		temp = f_freenull(temp);
	}
}

void	f_add_in(t_meta *ms, char *add)
{
	char	*temp;
	char	*prov;

	temp = ft_strdup(add);
	if (ms->in == NULL)
	{
		ms->in = ft_strdup(temp);
		temp = f_freenull(temp);
	}
	else
	{
		prov = ms->in;
		ms->in = f_join_char(prov, 29);
		prov = f_freenull(prov);
		prov = ms->in;
		ms->in = ft_strjoin(prov, temp);
		prov = f_freenull(prov);
		temp = f_freenull(temp);
	}
}

void	f_add_out(t_meta *ms, char *add)
{
	char	*temp;
	char	*prov;

	temp = ft_strdup(add);
	if (ms->out == NULL)
	{
		ms->out = ft_strdup(temp);
		temp = f_freenull(temp);
	}
	else
	{
		prov = ms->out;
		ms->out = f_join_char(prov, 29);
		prov = f_freenull(prov);
		prov = ms->out;
		ms->out = ft_strjoin(prov, temp);
		prov = f_freenull(prov);
		temp = f_freenull(temp);
	}
}

void	f_check_node(t_meta *ms)
{
	t_pars	*temp;

	temp = ms->list;
	while (temp && temp->txt)
	{
		if ((temp->txt[0] == 62 || temp->txt[0] == 60) && (temp->next == NULL
				|| temp->next->txt == NULL || temp->next->txt[0] == 124
				|| temp->next->txt[0] == 62 || temp->next->txt[0] == 60))
		{
			ms->exit_status = 2;
			ms->error_flag = ms->exit_status;
			f_free_list(&ms->list);
			return ;
		}
		else if ((temp->txt[0] == 124) && (temp->next == NULL
				|| temp->next->txt == NULL || temp->next->txt[0] == 124))
		{
			ms->exit_status = 2;
			ms->error_flag = ms->exit_status;
			f_free_list(&ms->list);
			return ;
		}
		else
			temp = temp->next;
	}
}

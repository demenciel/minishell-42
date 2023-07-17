
#include "../../inc/minishell.h"

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
		ms->com_temp = f_join_char(ms->com_temp, 29);
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
		ms->in = f_join_char(ms->in, 29);
		ms->in = ft_strjoin(ms->in, temp);
		free(temp);
		temp = NULL;
	}
}

void	f_add_out(t_meta *ms, char *add)
{
	// printf("" GRE "---f_add_out in---\n" WHT ""); // TODO Supprimer
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
		ms->out = f_join_char(ms->out, 29);
		ms->out = ft_strjoin(ms->out, temp);
		free(temp);
		temp = NULL;
	}
	// printf("" GRE "---f_add_out out---\n" WHT ""); // TODO Supprimer
}

int	f_check_env(char c)
{
	if (ft_isalnum(c) == 1 || c == '_' || c == '?')
		return (1);
	else
		return (0);
}

void f_check_node(t_meta *ms)
{
	printf("" GRE "---f_check_node in---\n" WHT ""); // TODO Supprimer
	t_pars *temp;

	temp = ms->list;
	while (temp)
	{
		if ((temp->next == NULL || temp->next->txt == NULL ||
		temp->next->txt[0] == 60 || temp->next->txt[0] == 62 ||
		temp->next->txt[0] == '\0') && (temp->txt[0] == 60 ||
		temp->txt[0] == 62))
			f_all_clean(ms, "Erreur redir node");
		else if ((temp->next == NULL || temp->next->txt == NULL ||
		temp->next->txt[0] == 124 || temp->next->txt[0] == '\0') &&
		(temp->txt[0] == 124))
			f_all_clean(ms, "Erreur pipe node");
		else
			temp = temp->next;
	}
	printf("" GRE "---f_check_node out---\n" WHT ""); // TODO Supprimer
}

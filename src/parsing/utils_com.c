
#include "../../inc/minishell.h"

void	f_add_com(t_meta *ms, char *add)
{
	char *temp;
	char *prov;

	temp = ft_strdup(add);
	if (ms->com_temp == NULL)
	{
		ms->com_temp = ft_strdup(temp);
		f_free_null(temp);
	}
	else
	{
		prov = ms->com_temp;
		ms->com_temp = f_join_char(prov, 29);
		f_free_null(prov);
		prov = ms->com_temp;
		ms->com_temp = ft_strjoin(prov, temp);
		f_free_null(prov);
		f_free_null(temp);
	}
}

void	f_add_in(t_meta *ms, char *add)
{
	char *temp;
	char *prov;

	temp = ft_strdup(add);
	if (ms->in == NULL)
	{
		ms->in = ft_strdup(temp);
		f_free_null(temp);
	}
	else
	{
		prov = ms->in;
		ms->in = f_join_char(prov, 29);
		f_free_null(prov);
		prov = ms->in;
		ms->in = ft_strjoin(prov, temp);
		f_free_null(prov);
		f_free_null(temp);
	}
}

void	f_add_out(t_meta *ms, char *add)
{
	printf("" GRE "---f_add_out in---\n" WHT ""); // TODO Supprimer
	char *temp;
	char *prov;
	temp = ft_strdup(add);
	if (ms->out == NULL)
	{
		ms->out = ft_strdup(temp);
		f_free_null(temp);
	}
	else
	{
		prov = ms->out;
		ms->out = f_join_char(prov, 29);
		f_free_null(prov);
		prov = ms->out;
		ms->out = ft_strjoin(prov, temp);
		f_free_null(prov);
		f_free_null(temp);
	}
	printf("" GRE "---f_add_out out---\n" WHT ""); // TODO Supprimer
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
	while (temp && temp->txt)
	{
		if ((temp->txt[0] == 62 || temp->txt[0] == 60) &&
		(temp->next == NULL || temp->next->txt == NULL ||
		temp->next->txt[0] == 124 || temp->next->txt[0] == 62 || temp->next->txt[0] == 60))
			f_all_clean(ms, "Erreur redir node");
		else if ((temp->txt[0] == 124) && (temp->next == NULL || temp->next->txt == NULL ||
		temp->next->txt[0] == 124))
			f_all_clean(ms, "Erreur pipe node");
		else
			temp = temp->next;
	}
	printf("" GRE "---f_check_node out---\n" WHT ""); // TODO Supprimer
}

void	f_free_null(void *str)
{
	free(str);
	str = NULL;
}
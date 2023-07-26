#include "../../inc/minishell.h"

void	f_free_null_meta(t_meta *ms)
{
	if (DEBUG == 1)
		printf("" GRE "---f_free_null_meta in---\n" WHT ""); // TODO Supprimer

	if (ms->line)
		ms->line = f_freenull(ms->line);
	if (ms->com_temp)
		ms->com_temp = f_freenull(ms->com_temp);
	if (ms->in)
		ms->in = f_freenull(ms->in);
	if (ms->out)
		ms->out = f_freenull(ms->out);
	ms->i = 0;
	if (ms->list)
	{
		f_free_list(&ms->list);
		ms->list = NULL;
	}
	if (ms->comand)
	{
		f_free_comand(&ms->comand);
		ms->comand = NULL;
	}
	ms->error_flag = 0;

	if (DEBUG == 1)
		printf("" GRE "---f_free_null_meta out---\n" WHT ""); // TODO Supprimer
}

void	f_free_comand(t_comand **list)
{
	if (DEBUG == 1)
		printf("" GRE "---f_free_comand in---\n" WHT ""); // TODO Supprimer

	t_comand	*temp;

	if (!*list || !list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->stin);
		free((*list)->stout);
		if ((*list)->com)
			ft_free_tab_char((*list)->com);
		free(*list);
		(*list) = temp;
	}
	*list = NULL;

	if (DEBUG == 1)
		printf("" GRE "---f_free_comand out---\n" WHT ""); // TODO Supprimer
}

void	f_free_list(t_pars **list)
{
	if (DEBUG == 1)
		printf("" GRE "---f_free_list in---\n" WHT ""); // TODO Supprimer

	t_pars	*temp;

	if (!*list || !list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->txt);
		free(*list);
		(*list) = temp;
	}
	*list = NULL;

	if (DEBUG == 1)
		printf("" GRE "---f_free_lsit out---\n" WHT ""); // TODO Supprimer
}

void	*f_freenull(void *str)
{
	if(str)
		free(str);
	return (NULL);
}

void	f_all_clean(t_meta *ms, char *msg)
{
	if (ms->line)
		free(ms->line);
	if (ms->comand)
		f_free_comand(&ms->comand);
	if (ms->com_temp)
		free(ms->com_temp);
	if (ms->in)
		free(ms->in);
	if (ms->out)
		free(ms->out);
	if (ms->list)
		f_free_list(&ms->list);
	free(ms);
	if (g()->export_list)
        ft_2darr_free(g()->export_list);
    if (g()->env_list)
        ft_2darr_free(g()->env_list);
	close(g()->in_fd);
	if (msg)
	{
		printf("%s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}


void	f_all_clean_exit(t_meta *ms, int nb)
{
	int i;

	i = nb;
	if (ms->line)
		free(ms->line);
	if (ms->comand)
		f_free_comand(&ms->comand);
	if (ms->com_temp)
		free(ms->com_temp);
	if (ms->in)
		free(ms->in);
	if (ms->out)
		free(ms->out);
	if (ms->list)
		f_free_list(&ms->list);
	if (g()->export_list)
        ft_2darr_free(g()->export_list);
    if (g()->env_list)
        ft_2darr_free(g()->env_list);
	close(g()->in_fd);
	free(ms);
	exit(i);
}

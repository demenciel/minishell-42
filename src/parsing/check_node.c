
#include "../../inc/minishell.h"

void	f_pars_list(t_meta *ms)
{
	printf (""GRE"---f_pars_list in---\n"WHT""); //TODO Supprimer

	t_pars *temp;

	temp = ms->list;
	while (ms->list)
	{
		printf("you\n");
		if (ms->list->txt[0] == 36)
		{
			printf("here\n");
			ms->list->txt = f_pars_dollar(ms->list->txt);
		}
		else if (ms->list->txt[0] == 124 && ft_strlen(ms->list->txt) > 1)
			f_all_clean(ms, "Erreur de pipes");
		else if (ms->list->txt[0] == 62 && ft_strlen(ms->list->txt) > 2)
			f_all_clean(ms, "Erreur de >");
		else if (ms->list->txt[0] == 60 && ft_strlen(ms->list->txt) > 2)
			f_all_clean(ms, "Erreur de <");
		else
			ms->list = ms->list->next;
	}
	ms->list = temp;
	printf (""RED"---f_pars_list out---\n"WHT""); //TODO Supprimer
}

char	*f_pars_dollar(char *txt)
{
	printf (""GRE"---f_pars_dollar in---\n"WHT""); //TODO Supprimer
	char *temp;


	txt = ft_strtrim(txt, "$");
	temp = getenv(txt);
	printf (" in %s\n", temp); //TODO Supprimer
	if(temp == NULL)
		txt = "env doesn't";
	else
		txt = ft_strdup(temp);
	return (txt);
	printf (""RED"---f_pars_dollar out---\n"WHT""); //TODO Supprimer
}

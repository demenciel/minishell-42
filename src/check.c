
#include "../inc/minishell.h"

void	f_check_pipes(t_meta *ms)
{
	int	start;
	int	end;

	printf("" GRE "---f_check_pipes in---\n" WHT ""); // TODO Supprimer
	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 124)
		ms->i++;
	end = ms->i;
	if (end - start > 1)
		f_all_clean(ms, "Erreur de pipes");
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end
					- start))));
	printf("" RED "---f_check_pipes out---\n" WHT ""); // TODO Supprimer
}

void	f_check_redir_right(t_meta *ms)
{
	int	start;
	int	end;
	char *temp;

	printf("" GRE "---f_check_redir_right in---\n" WHT ""); // TODO Supprimer
	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 62)
		ms->i++;
	end = ms->i;
	if (end - start > 2)
		f_all_clean(ms, "Erreur de redir right");
	temp = ft_substr(ms->line, start, (end - start));
	f_addback_node(&ms->list, f_new_node(temp));
	printf("" RED "---f_check_redir_right out---\n" WHT ""); // TODO Supprimer
}

void	f_check_redir_left(t_meta *ms)
{
	int	start;
	int	end;

	printf("" GRE "---f_check_redir_left in---\n" WHT ""); // TODO Supprimer
	start = ms->i;
	while (ms->line[ms->i] && ms->line[ms->i] == 60)
		ms->i++;
	end = ms->i;
	if (end - start > 2)
		f_all_clean(ms, "Erreur de redir left");
	
	f_addback_node(&ms->list, f_new_node(ft_substr(ms->line, start, (end
					- start))));
	printf("" RED "---f_check_redir_left out---\n" WHT ""); // TODO Supprimer
}

void	f_check_single_quote(t_meta *ms)
{
	int		start;
	int		end;
	char	*temp;

	printf("" GRE "---f_check_single_quote in---\n" WHT ""); // TODO Supprimer
	start = ms->i++;
	while (ms->line[ms->i] != 39 && ms->line[ms->i])
		ms->i++;
	end = ms->i++;
	temp = ft_substr(ms->line, start, (end - start) + 1);
	temp = f_pars_simple_quote(ms, temp);
	f_addback_node(&ms->list, f_new_node(temp));
	printf("" RED "---f_check_single_quote out---\n" WHT ""); // TODO Supprimer
}

void	f_check_double_quote(t_meta *ms)
{
	int		start;
	int		end;
	char	*temp;

	printf("" GRE "---f_check_double_quote in---\n" WHT ""); // TODO Supprimer
	start = ms->i++;
	while (ms->line[ms->i] != 34 && ms->line[ms->i])
		ms->i++;
	end = ms->i++;
	temp = ft_substr(ms->line, start, (end - start) + 1);
	temp = f_pars_double_quote(ms, temp);
	f_addback_node(&ms->list, f_new_node(temp));
	printf("" RED "---f_check_double_quote out---\n" WHT ""); // TODO Supprimer
}

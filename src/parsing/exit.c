#include "../../inc/minishell.h"

int	f_exit(t_meta *ms)
{
	int i;
	int nb;

	i = f_size_table(ms->comand->com);
	if (i > 2)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("exit: too many arguments", 2);
		ms->exit_status = 1;
		return (0);
	}
	else if (i == 2 && f_arg_is_num(ms->comand->com[1]) == -1)
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(ms->comand->com[1], 1);
		f_all_clean(ms, ": numeric argument required");
	}
	else if (i == 2)
	{
		nb = ft_atoi(ms->comand->com[1]);
		if (nb > 256)
			nb = nb % 256;
		f_all_clean_exit(ms, nb);
	}
	f_all_clean(ms, NULL);
	return (0);
}

int f_size_table(char **table)
{
	int i;

	i = 0;
	if (!table || *table == NULL)
		return (i);
	while (table[i])
		i++;
	return (i);
}

int	f_arg_is_num(char *txt)
{
	int i;

	i = 0;
	while (txt[i])
	{
		if (ft_isalpha(txt[i]) == 1)
			return (-1);
		i++;
	}
	return (0);
}

char	*f_error_message(int nb)
{

	if (nb == 2)
		return ("syntax error near unexpted token");
	else if (nb == 8)
		return ("permission denied");
	else if (nb == 127)
		return ("command not found");
	else if (nb == 130)
		return ("Ctr_C");
	else if (nb == 1)
		return ("not a valid identifier");
	return (NULL);
}

#include "../../inc/minishell.h"

void	f_sighandler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	f_sighandler_com(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}


void	f_signals(int nb)
{
	if (nb == 1)
	{
		signal(SIGQUIT, f_sighandler);
		signal(SIGINT, f_sighandler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (nb == 2)
	{
		signal(SIGQUIT, f_sighandler_com);
		signal(SIGINT, f_sighandler_com);
	}
}

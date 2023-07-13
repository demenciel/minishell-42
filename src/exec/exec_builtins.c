#include "../../inc/minishell.h"

void    find_builtins(char *cmd)
{
    if (strcmp(cmd, "export") == 0)
    {
        printf("yoo");
        ft_export("");
    }
}

void    ft_check_builtins(t_comand *t_cmd)
{
    int i;

    i = 0;
    while (t_cmd != NULL)
    {
        find_builtins(t_cmd->com[i]);
        t_cmd = t_cmd->next;
    }
}
// iterer dans la liste de node first command to execute builtins
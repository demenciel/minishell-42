#include "../../inc/minishell.h"

void    find_export_unset_env(t_comand *node)
{
    if (ft_strcmp(node->com[0], "export") == 0)
    {
        int i;

        i = 1;
            
        if (!node->com[i])
            ft_export("");
        while (node->com[i])
        {
            ft_export(node->com[i++]);
        }
    }
    else if (ft_strcmp(node->com[0], "unset") == 0)
    {
        int i;

        i = 1;
        if (!node->com[i])
            ft_unset("");
        while (node->com[i])
            ft_unset(node->com[i++]);
    }
    else if (ft_strcmp(node->com[0], "env") == 0)
        ft_env();
}


void    find_builtins(t_comand *node)
{
    find_export_unset_env(node);
}

void    ft_check_builtins(t_comand *t_cmd)
{
    int i;

    i = 0;
    while (t_cmd != NULL)
    {
        find_builtins(t_cmd);
        t_cmd = t_cmd->next;
    }
}
// iterer dans la liste de node first command to execute builtins
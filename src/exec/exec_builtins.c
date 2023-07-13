#include "../../inc/minishell.h"


void    find_builtins(t_comand *node)
{
    if (ft_strcmp(node->com[0], "export") == 0)
    {
        printf("%s\n\n", node->com[0]);
        printf("%s\n\n", node->com[1]);
        // if (node->com[1])
        //     ft_export(node->com[1]);
        // else
        //     ft_export("");
    }
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
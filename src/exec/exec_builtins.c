#include "../../inc/minishell.h"

/**
 * @brief Checks the content of the node, and executes the builtin depending of the content of the node
*/
void    find_export_unset_env(t_comand *node)
{
    int i;

    if (ft_strcmp(node->com[0], "export") == 0)
    {
        i = 1;
        if (!node->com[i])
            ft_export("");
        while (node->com[i])
        {
            ft_export(node->com[i]);
            i++;
        }
    }
    else if (ft_strcmp(node->com[0], "unset") == 0)
    {
        i = 1;
        if (!node->com[i])
            ft_unset("");
        while (node->com[i])
            ft_unset(node->com[i++]);
    }
    else if (ft_strcmp(node->com[0], "env") == 0)
        ft_env();
}

/**
 * @brief A function to separate the execution of the builtins
*/
void    find_builtins(t_comand *node)
{
    find_export_unset_env(node);
}

/**
 * @brief Iterates in the comand linked list to find the builtins to execute
*/
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

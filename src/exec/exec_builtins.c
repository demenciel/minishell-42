#include "../../inc/minishell.h"

/**
 * @brief Checks the content of the node, and executes the builtin depending of the content of the node
*/
void find_export_unset_env(t_comand *node, int input_fd)
{
    int i;

    if (ft_strcmp(node->com[0], "export") == 0)
    {
        i = 1;
        if (!node->com[i])
            ft_export("", input_fd);
        while (node->com[i])
        {
            ft_export(node->com[i], input_fd);
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
        ft_env(input_fd);
}


/**
 * @brief A function to separate the execution of the builtins
*/
void    find_builtins(t_comand *node, int input_fd)
{
    find_export_unset_env(node, input_fd);
}

/**
 * @brief Iterates in the comand linked list to find the builtins to execute
*/
bool    ft_check_builtins(char **cmd)
{
    if (ft_strcmp(cmd[0], "export") == 0) 
        return (true);
    else if (ft_strcmp(cmd[0], "unset") == 0) 
        return (true);
    else if (ft_strcmp(cmd[0], "env") == 0) 
        return (true);
    else if (ft_strcmp(cmd[0], "echo") == 0) 
        return (true);
    else if (ft_strcmp(cmd[0], "cd") == 0) 
        return (true);
    else if (ft_strcmp(cmd[0], "pwd") == 0) 
        return (true);
    else if (ft_strcmp(cmd[0], "exit") == 0) 
        return (true);
    return (false);
}

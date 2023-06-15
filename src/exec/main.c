

#include "../inc/minishell.h"

// EXEC
int main( int ac, char **av)
{
    (void)ac;
    (void)av;

    char *line = NULL;
    while (1)
    {
        line = readline("minishel >");
        add_history(line);
    }
    return (0);
}
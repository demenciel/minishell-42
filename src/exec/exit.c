// "bash: export: ʻ9HOLA=': not a valid identifier
// $>"

#include "../../inc/minishell.h"
#include <strings.h>

void    ft_exit(char *msg, char *builtin, int error)
{
    printf("Minishell: %s: '%s': not valid", builtin, msg);
    exit(error);
}
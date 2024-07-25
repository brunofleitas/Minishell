#include "minishell.h"

t_token *get_next_token(t_token **tkns) 
{
    static int i;

    if (!tkns[i])
        return (NULL);
    return (tkns[i++]);
}
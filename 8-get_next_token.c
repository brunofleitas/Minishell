#include "minishell.h"

t_token *get_next_token(t_token **tokens) 
{
    static int i;

    if (!tokens[i])
        return (NULL);
    return (tokens[i++]);
}
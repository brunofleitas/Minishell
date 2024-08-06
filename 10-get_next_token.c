#include "minishell.h"

t_token *get_next_token(t_token **tkns, int t) 
{
    static int i;

    if (t == 0)
    {
        i = 0;
        return  (NULL);
    }
    if (!tkns[i])
    {
        return (NULL);
    }
    return (tkns[i++]);
}
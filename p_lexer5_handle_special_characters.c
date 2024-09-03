#include "minishell.h"

void handle_special_characters(char *input, int start, t_ma *ma)
{
    if (ft_strchr("$;|&><", input[start]))
    {
        ma->toks[ma->tok_count++] = (t_tok)
        {
            .type = TOKEN_SPECIAL_CHAR,
            .value = ft_strndup_g_c(input + start, 1, &(ma->first_node)),
            .start_pos = start,
            .end_pos = start
        };
        start++;
    }
}
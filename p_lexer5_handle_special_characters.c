#include "minishell.h"

void handle_special_characters(char *input, int start, t_ma *ma)
{
    // Step 5: Process Special Characters and Operators
    if (strchr("$;|&><", input[start]))
    {
        ma->toks[ma->tok_count++] = (t_tok)
        {
            .type = TOKEN_SPECIAL_CHAR,
            .value = strndup(input + start, 1),
            .start_pos = start,
            .end_pos = start
        };
        start++;
    }
}
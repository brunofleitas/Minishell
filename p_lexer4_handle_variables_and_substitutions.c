#include "minishell.h"

static int handle_variable(char *input, int start, t_ma *ma)
{
    char *var_name;
    char *var_value;

    int end = start + 1;
    while (ft_isalnum(input[end]) || input[end] == '_')
        end++;
    var_name = ft_substr(input, start + 1, end - start - 1);
    var_value = getenv(var_name);
    ma->toks[ma->tok_count] = (t_tok)
    {
        .type = TOKEN_VARIABLE,
        .value = var_value ? ft_strdup(var_value) : ft_strdup(""),
        .start_pos = start,
        .end_pos = end - 1
    };
    free(var_name);
    return (end - 1);
}

static int handle_command_sub(char *input, int start, t_ma *ma)
{
    int end = start + 1;
    int depth = 1;
    while (input[end] && depth > 0)
    {
        if (input[end] == '(')
            depth++;
        else if (input[end] == ')')
            depth--;
        end++;
    }
    ma->toks[ma->tok_count] = (t_tok)
    {
        .type = TOKEN_COMMAND_SUBSTITUTION,
        .value = ft_substr(input, start + 2, end - start - 3),
        .start_pos = start,
        .end_pos = end - 1
    };
    return (end - 1);
}

void handle_variables_and_substitutions(char *input, int start, t_ma *ma)
{
    while (input[start])
    {
        if (input[start] == '$' && input[start + 1])
        {
            if (input[start + 1] == '(')
            {
                ma->tok_count++;
                start = handle_command_sub(input, start, ma);
            }
            else
            {
                ma->tok_count++;
                start = handle_variable(input, start, ma);
            }
        }
        else
        {
            ma->toks[ma->tok_count++] = (t_tok)
            {
                .type = TOKEN_WORD,
                .value = ft_substr(input, start, 1),
                .start_pos = start,
                .end_pos = start
            };
        }
        start++;
    }
}

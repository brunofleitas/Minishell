#include "minishell.h"

static int should_combine(t_tok *token1, t_tok *token2) 
{
    if (token1->type == TOKEN_WORD && token2->type == TOKEN_VARIABLE)
        return 1;
    if (token1->type == TOKEN_WORD && token2->type == TOKEN_COMMAND_SUBSTITUTION)
        return 1;
    if (token1->type == TOKEN_VARIABLE && token2->type == TOKEN_WORD)
        return 1;
    if (token1->type == TOKEN_COMMAND_SUBSTITUTION && token2->type == TOKEN_WORD)
        return 1;
    return (0);
}

static void merge_tokens(t_tok *dest, t_tok *src1, t_tok *src2)
{
    dest->type = TOKEN_WORD;
    dest->start_pos = src1->start_pos;
    dest->end_pos = src2->end_pos;
    int len1 = strlen(src1->value);
    int len2 = strlen(src2->value);
    dest->value = malloc(len1 + len2 + 1);
    strcpy(dest->value, src1->value);
    strcat(dest->value, src2->value);
}

static void shift_tokens(t_ma *ma, int start_index)
{
    for (int i = start_index; i < ma->tok_count - 1; i++)
    {
        ma->toks[i] = ma->toks[i + 1];
    }
    (ma->tok_count)--;
}

void combine_tokens(t_ma *ma)
{
    int i = 0;
    while (i < ma->tok_count - 1) 
    {
        if (should_combine(&(ma->toks[i]), &(ma->toks[i + 1])))
        {
            merge_tokens(&(ma->toks[i]), &(ma->toks[i]), &(ma->toks[i + 1]));
            shift_tokens(ma, i + 1);
        } else
        {
            i++;
        }
    }
}
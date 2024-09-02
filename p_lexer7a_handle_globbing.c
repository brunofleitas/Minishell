#include "minishell.h"

#include "minishell.h"

static void replace_token_with_expansion(t_ma *ma, int index, t_wcs_args *args);

/**
 * @brief Handles globbing (wildcard expansion) for tokens in the input.

 * This function processes each token in the input, expanding any wildcards
 * found. It supports '*' (any number of characters), '?' (single character),
 * and '[...]' (character class) patterns. It uses a recursive approach to
 * handle nested directory structures.
 * 
 * @param input The original input string (unused in this implementation).
 * @param ma The memory allocator structure containing tokens and other data.
 * @return void
 * 
 * @note This function modifies the token array in place, replacing wildcard
 * patterns with their expanded matches.
 * @note It relies on helper functions for pattern matching and token manipulation.
 * @note Memory allocation failures during expansion will result in the token
 * being left unexpanded.
 */
void handle_globbing(char *input, t_ma *ma)
{
    int i;
    t_wcs_args args;

    for (i = 0; i < ma->tok_count; i++)
    {
        if (ft_strchr(ma->toks[i].value, '*') || ft_strchr(ma->toks[i].value, '?') ||
            ft_strchr(ma->toks[i].value, '['))
        {
            ft_memset(&args, 0, sizeof(t_wcs_args));
            args.orig_token = ma->toks[i].value;
            if (expand_wildcard(&args, args.orig_token, ma))
            {
                replace_token_with_expansion(ma, i, &args);
                i += args.count_match - 1;  // Skip newly added tokens
            }
        }
    }
}

/**
 * @brief Replaces a token with its wildcard expansion results.
 * 
 * This function replaces the original wildcard token with the expanded
 * matches. If no matches were found, the original token is left unchanged.
 * 
 * @param ma The memory allocator structure containing tokens and other data.
 * @param index The index of the token to be replaced.
 * @param args The wildcard arguments structure containing expansion results.
 * @return void
 * 
 * @note This function modifies the token array in place.
 * @note If memory allocation fails during the process, the original token
 * is left unchanged.
 */
static void replace_token_with_expansion(t_ma *ma, int index, t_wcs_args *args)
{
    int i;
    t_tok *new_tokens;

    if (args->count_match == 0)
        return;
    new_tokens = ft_calloc_g_c(ma->tok_count + args->count_match - 1, 
                               sizeof(t_tok), &(ma->first_node));
    if (!new_tokens)
        return;
    ft_memcpy(new_tokens, ma->toks, index * sizeof(t_tok));
    for (i = 0; i < args->count_match; i++)
    {
        new_tokens[index + i].type = TOKEN_WORD;
        new_tokens[index + i].value = args->matches[i];
        new_tokens[index + i].start_pos = ma->toks[index].start_pos;
        new_tokens[index + i].end_pos = ma->toks[index].end_pos;
    }
    ft_memcpy(&new_tokens[index + args->count_match], &ma->toks[index + 1],
              (ma->tok_count - index - 1) * sizeof(t_tok));
    ma->tok_count += args->count_match - 1;
    ma->toks = new_tokens;
}
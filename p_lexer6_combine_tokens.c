#include "minishell.h"

/**
 * @brief Determines if two adjacent tokens should be combined.
 *
 * This function checks if two tokens should be merged based on their types.
 * It combines tokens in the following cases:
 * 1. WORD followed by VARIABLE
 * 2. WORD followed by COMMAND_SUBSTITUTION
 * 3. VARIABLE followed by WORD
 * 4. COMMAND_SUBSTITUTION followed by WORD
 *
 * @param token1 Pointer to the first token.
 * @param token2 Pointer to the second token.
 * @return int Returns 1 if the tokens should be combined, 0 otherwise.
 *
 * @note This function is crucial for handling complex shell expansions and concatenations.
 */
static int should_combine(t_tok *token1, t_tok *token2) 
{
    if (token1->type == TOKEN_WORD && token2->type == TOKEN_VARIABLE)
        return (1);
    if (token1->type == TOKEN_WORD && token2->type == TOKEN_COMMAND_SUBSTITUTION)
        return (1);
    if (token1->type == TOKEN_VARIABLE && token2->type == TOKEN_WORD)
        return (1);
    if (token1->type == TOKEN_COMMAND_SUBSTITUTION && token2->type == TOKEN_WORD)
        return (1);
    return (0);
}

/**
 * @brief Merges two tokens into a single token.
 *
 * This function combines the values of two source tokens into a single destination token.
 * The resulting token has the following properties:
 * - Type: Always set to TOKEN_WORD
 * - Start position: Taken from the first source token
 * - End position: Taken from the second source token
 * - Value: Concatenation of both source token values
 *
 * @param dest Pointer to the destination token where the result will be stored.
 * @param src1 Pointer to the first source token.
 * @param src2 Pointer to the second source token.
 *
 * @note This function dynamically allocates memory for the new token value.
 * @note The caller is responsible for freeing the memory of the original token values if necessary.
 */
static void merge_tokens(t_tok *dest, t_tok *src1, t_tok *src2, t_ma *ma)
{
    int len1;
    int len2;

    dest->type = TOKEN_WORD;
    dest->start_pos = src1->start_pos;
    dest->end_pos = src2->end_pos; 
    len2 = ft_strlen(src2->value);
    len1 = ft_strlen(src1->value);
    dest->value = g_c(&(ma->first_node), len1 + len2 + 1);
    ft_strlcpy(dest->value, src1->value, len1 + len2 + 1);
    ft_strlcat(dest->value, src2->value, len1 + len2 + 1);
}

/**
 * @brief Shifts tokens in the token array after combining two tokens.
 *
 * This function moves all tokens one position to the left starting from the given index,
 * effectively removing one token from the array. It's used after combining two tokens
 * to ensure the token array remains contiguous.
 *
 * @param ma Pointer to the main structure containing token information.
 * @param start_index The starting index from which to shift tokens.
 *
 * @note This function decrements the token count in the ma structure.
 * @note It does not free any memory associated with the removed token.
 */
static void shift_tokens(t_ma *ma, int start_index)
{
    int i;

    i = start_index;
    while(i < ma->tok_count - 1)
    {
        ma->toks[i] = ma->toks[i + 1];
        i++;
    }
    (ma->tok_count)--;
}

/**
 * @brief Combines adjacent tokens in the token array based on specified rules.
 *
 * This function iterates through the token array, combining adjacent tokens
 * when necessary according to the rules defined in should_combine().
 * The process involves:
 * 1. Checking if adjacent tokens should be combined
 * 2. Merging the tokens if needed
 * 3. Shifting the remaining tokens to fill the gap
 *
 * @param ma Pointer to the main structure containing token information.
 *
 * @note This function modifies the token array in-place.
 * @note The token count in ma is updated to reflect the new number of tokens after combining.
 */
void combine_tokens(t_ma *ma)
{
    int i = 0;
    while (i < ma->tok_count - 1) 
    {
        if (should_combine(&(ma->toks[i]), &(ma->toks[i + 1])))
        {
            merge_tokens(&(ma->toks[i]), &(ma->toks[i]), &(ma->toks[i + 1]), ma);
            shift_tokens(ma, i + 1);
        } 
        else
            i++;
    }
}
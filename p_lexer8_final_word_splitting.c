#include "minishell.h"

/**
 * @brief Determines if a character is an IFS (Internal Field Separator) character.
 *
 * This function checks if the given character is present in the IFS string.
 * Currently, it uses a default IFS of space, tab, and newline characters.
 *
 * @param c The character to check.
 * @return int Returns 1 if the character is an IFS character, 0 otherwise.
 *
 * @note This function currently uses a hardcoded IFS. In a full implementation,
 *       it should retrieve the IFS from the environment using getenv("IFS").
 *       However getenv is not allowed.
 */
static int is_ifs_char(char c)
{
    const char *ifs;
    
    //  = getenv("IFS");
    // if (!ifs)
    ifs = " \t\n";  // Default IFS
    return (ft_strchr(ifs, c) != NULL);
}

/**
 * @brief Counts the number of words in a string based on IFS characters.
 *
 * This function traverses the string, counting sequences of non-IFS characters
 * as words. It uses the is_ifs_char function to determine word boundaries.
 *
 * @param str The string to count words in.
 * @return int The number of words found in the string.
 *
 * @note This function is used to determine the number of tokens that will result
 *       from splitting a word token.
 */
static int count_words(const char *str)
{
    int     count;
    int     in_word;

    count = 0;
    in_word = 0;
    while (*str) {
        if (is_ifs_char(*str))
            in_word = 0;
        else if (!in_word) 
        {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

/**
 * @brief Splits a token into multiple tokens based on IFS characters.
 *
 * This function takes a single token and splits its value into multiple tokens
 * wherever IFS characters are found. The resulting tokens are stored in the
 * new_tokens array.
 *
 * @param token The original token to split.
 * @param new_tokens Array to store the resulting split tokens.
 * @param new_count Pointer to the count of new tokens, updated by this function.
 * @param ma Pointer to the main structure containing memory management information.
 *
 * @note This function uses the garbage collection mechanism (g_c) for memory allocation.
 * @note The start_pos and end_pos of the new tokens are adjusted based on the original token's position.
 */
static void split_token(t_tok *token, t_tok *new_tokens, int *new_count, t_ma *ma) 
{
    char    *str;
    int     start;
    int     i;

    str = token->value;
    start = 0;
    i = 0;
    while (str[i]) {
        if (is_ifs_char(str[i])) {
            if (i > start) {
                new_tokens[(*new_count)++] = (t_tok)
                {
                    .type = TOKEN_WORD,
                    .value = ft_strndup_g_c(str + start, i - start, &(ma->first_node)),
                    .start_pos = token->start_pos + start,
                    .end_pos = token->start_pos + i - 1
                };
            }
            start = i + 1;
        }
        i++;
    }
    if (i > start) {
        new_tokens[(*new_count)++] = (t_tok)
        {
            .type = TOKEN_WORD,
            .value = ft_strndup_gc(str + start, i - start, &(ma->first_node)),
            .start_pos = token->start_pos + start,
            .end_pos = token->end_pos
        };
    }
}

/**
 * @brief Performs final word splitting on all word tokens in the token array.
 *
 * This function iterates through all tokens in ma->toks, splitting any TOKEN_WORD
 * tokens based on IFS characters. Non-word tokens are copied as-is. The resulting
 * tokens replace the original token array.
 *
 * @param ma Pointer to the main structure containing token and memory management information.
 *
 * @note This function allocates a new array for tokens, which may be significantly larger
 *       than the original (up to 10 times). The actual size needed is not pre-calculated.
 * @note After processing, the original token array is replaced with the new one, and the
 *       token count (ma->tok_count) is updated.
 * @note Memory for the temporary new_tokens array is freed using the garbage collection mechanism.
 */
void final_word_splitting(t_ma *ma)
{
    t_tok   *new_tokens;
    int     new_count;
    int     i;

    i = 0;
    new_count = 0;
    new_tokens = g_c(ma->tok_count * 10 * sizeof(t_tok), &(ma->first_node));
    while(i < ma->tok_count)
    {
        if (ma->toks[i].type == TOKEN_WORD) 
        {
            split_token(&(ma->toks[i]), new_tokens, &new_count, ma);
        } else {
            new_tokens[new_count++] = ma->toks[i];
        }
        i++;
    }
    ft_memcpy(ma->toks, new_tokens, sizeof(t_tok) * new_count);
    free_ntc_prior(&(ma->first_node), new_tokens);
    ma->tok_count = new_count;
}
#include "minishell.h"

/**
 * Checks if a character is a special character.
 * Special characters include '$', ';', '|', '&', '>', and '<'.
 *
 * @param c The character to check.
 * @return 1 if the character is a special character, 0 otherwise.
 */
static int is_special_char(char c)
{
    return (c == '$' || c == ';' || c == '|' || c == '&' || c == '>' || c == '<');
}

/**
 * Handles a word in the input string and creates a token for it.
 * 
 * @param input The input string.
 * @param start The starting index of the word.
 * @param ma The main structure containing tokens.
 * @return The ending index of the word.
 */

static int handle_word(char *input, int start, t_ma *ma)
{
    int end;
    
    end = start;
    while (input[end] && !ft_isspace(input[end]) && !is_special_char(input[end]))
        end++;
    ma->toks[ma->tok_count] = (t_tok)
    {
        .type = TOKEN_WORD,
        .value = ft_substr(input, start, end - start),
        .start_pos = start,
        .end_pos = end - 1
    };
    return (end - 1);
}

/**
 * @brief Handles special characters in the input string and creates a token for it.
 * 
 * This function takes an input string, a starting position, and a pointer to a t_ma structure.
 * It creates a token of type TOKEN_SPECIAL_CHAR for the special character at the starting position.
 * The token's value is set to a substring of the input string containing the special character.
 * The token's start and end positions are set to the starting position.
 * 
 * @param input The input string.
 * @param start The starting position of the special character.
 * @param ma A pointer to a t_ma structure.
 * @return The starting position of the special character.
 */
static int handle_special_char(char *input, int start, t_ma *ma)
{
    ma->toks[ma->tok_count] = (t_tok)
    {
        .type = TOKEN_SPECIAL_CHAR,
        .value = ft_substr(input, start, 1),
        .start_pos = start,
        .end_pos = start
    };
    return (start);
}

/**
 * @brief Tokenizes the input string starting from the specified index.
 * 
 * This function tokenizes the input string by iterating through each character
 * starting from the specified index. It counts the number of tokens and calls
 * the appropriate functions to handle special characters or words.
 * 
 * @param input The input string to be tokenized.
 * @param start The starting index for tokenization.
 * @param ma A pointer to the main structure containing tokenization information.
 */
void initial_tokenization(char *input, int start, t_ma *ma)
{
    while (input[start])
    {
        if (ft_isspace(input[start]))
            start++;
        else if (is_special_char(input[start]))
        {
            start = handle_special_char(input, start, ma);
            ma->tok_count++;
        }
        else
        {            
            start = handle_word(input, start, ma);
            ma->tok_count++;
        }        
        start++;
    }
}

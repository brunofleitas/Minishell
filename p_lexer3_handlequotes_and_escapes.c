#include "minishell.h"

/**
 * Handles single quotes in the input string.
 * 
 * @param input The input string.
 * @param start The starting index of the single quote.
 * @param ma The main structure containing tokens and other information.
 * @return The index of the character after the closing single quote.
 */
static int handle_single_quote(char *input, int start, t_ma *ma)
{
    int end;
    
    end = start + 1;
    while (input[end] && input[end] != '\'')
        end++;
    ma->toks[ma->tok_count] = (t_tok)
    {
        .type = TOKEN_QUOTE,
        .value = ft_substr(input, start + 1, end - start - 1),
        .start_pos = start,
        .end_pos = end
    };
    return (end);
}

/**
 * Handles the parsing of a double quote in the input string.
 * 
 * @param input The input string to be parsed.
 * @param start The starting index of the double quote.
 * @param ma The main structure containing the tokens and other information.
 * @return The ending index of the double quote.
 */
static int handle_double_quote(char *input, int start, t_ma *ma)
{
    int end;
    
    end = start + 1;
    while (input[end] && input[end] != '"')
    {
        if (input[end] == '\\' && input[end + 1])
            end++;
        end++;
    }
    ma->toks[ma->tok_count] = (t_tok)
    {
        .type = TOKEN_QUOTE,
        .value = ft_substr_g_c(input, start + 1, end - start - 1, &(ma->first_node)),
        .start_pos = start,
        .end_pos = end
    };
    return (end);
}

/**
 * Handles quotes and escapes in the input string.
 * 
 * @param input The input string to process.
 * @param start The starting index in the input string.
 * @param ma A pointer to the main structure.
 * @return The updated starting index.
 */
void handle_quotes_and_escapes(char *input, int start, t_ma *ma)
{
    // Iterate through the input string
    while (input[start])
    {
        // If a single quote is encountered
        if (input[start] == '\'')
        {
            start = handle_single_quote(input, start, ma);
            ma->tok_count++;
        }
        // If a double quote is encountered
        else if (input[start] == '"')
        {
            start = handle_double_quote(input, start, ma);
            ma->tok_count++;
        }
        // If a backslash is encountered
        else if (input[start] == '\\' && input[start + 1])
        {
            // Create a new token for the escaped character
            ma->toks[ma->tok_count++] = (t_tok)
            {
                .type = TOKEN_WORD,
                .value = ft_substr(input, start + 1, 1),
                .start_pos = start,
                .end_pos = start + 1
            };
            start++;
        }
        else
            ma->toks[ma->tok_count++] = (t_tok)
            {
                .type = TOKEN_WORD,
                .value = ft_substr(input, start, 1),
                .start_pos = start,
                .end_pos = start
            };
        start++;
    }
}
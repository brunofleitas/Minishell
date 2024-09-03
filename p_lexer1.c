#include "minishell.h"

/**
 * @brief Tokenizes an input string according to Bash-like shell syntax rules.
 *
 * This function performs a multi-step tokenization process that closely mimics
 * the behavior of Bash. It handles various shell syntax elements including:
 * - Whitespace separation
 * - Quoting and escape characters
 * - Variable expansion and command substitution
 * - Special characters and operators
 * - Token combination
 * - Filename expansion (globbing)
 * - Final word splitting
 *
 * The tokenization is performed in-place, modifying the token array (ma->toks)
 * as it progresses through each step.
 *
 * @param input The input string to be tokenized.
 * @param ma Pointer to the main structure containing token information and memory management data.
 * @return t_tok* Pointer to the array of tokenized elements.
 *
 * @note The function uses a fixed maximum token length (MAX_TOK_LEN).
 * @note Memory for tokens is allocated using a custom garbage collection mechanism.
 * @note The function adds a final NULL token to mark the end of the token array.
 */
t_tok *tokenize(char *input, t_ma *ma)
{
    int i = 0;

    // Allocate memory for tokens
    ma->toks = ft_calloc_g_c(MAX_TOK_LEN, sizeof(t_tok *), &(ma->first_node));
    ma->tok_count = 0;

    while (input[i] != '\0') 
    {
        // Step 2: Initial Tokenization by Whitespace
        initial_tokenization(input, i, ma);
        i = ma->toks[ma->tok_count - 1].end_pos + 1;

        // Step 3: Handle Quotes and Escape Characters
        handle_quotes_and_escapes(input, i, ma);
        i = ma->toks[ma->tok_count - 1].end_pos + 1;

        // Step 4: Recognize and Expand Variables and Substitutions
        handle_variables_and_substitutions(input, i, ma);
        i = ma->toks[ma->tok_count - 1].end_pos + 1;

        // Step 5: Process Special Characters and Operators
        handle_special_characters(input, i, ma);
        i = ma->toks[ma->tok_count - 1].end_pos + 1;

        // Step 6: Combine Tokens Where Necessary
        combine_tokens(ma);

        // Step 7: Handle Filename Expansion (Globbing)
        handle_globbing(input, ma);

        // Step 8: Perform Final Word Splitting
        final_word_splitting(ma);
    }
    ma->toks[ma->tok_count].type = TOKEN_WORD;
    ma->toks[ma->tok_count].value = NULL;
    ma->toks[ma->tok_count].start_pos = -1;
    ma->toks[ma->tok_count].end_pos = -1;
    return (ma->toks);
}

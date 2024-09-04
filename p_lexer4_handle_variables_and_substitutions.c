#include "minishell.h"

static void handle_variable_util(char *var_value, int start, int end,  t_ma *ma)
{
    if(var_value)
    {
        ma->toks[ma->tok_count] = (t_tok)
        {
            .type = TOKEN_VARIABLE,
            .value = ft_strdup_g_c(var_value, &(ma->first_node)),
            .start_pos = start,
            .end_pos = end - 1
        };
    }
    else
    {
        ma->toks[ma->tok_count] = (t_tok)
        {
            .type = TOKEN_VARIABLE,
            .value = ft_strdup_g_c("", &(ma->first_node)),
            .start_pos = start,
            .end_pos = end - 1
        };
    }
}

/**
 * @brief Handles variable expansion in the input string.
 * 
 * This function processes a variable (starting with '$') in the input string.
 * It extracts the variable name, looks up its value using getenv(),
 * and creates a token of type TOKEN_VARIABLE with the variable's value.
 * 
 * @param input The input string being processed.
 * @param start The starting index of the variable in the input string.
 * @param ma Pointer to the main structure containing token information.
 * @return int The ending index of the processed variable.
 * 
 * @note Supports alphanumeric characters and underscores in variable names.
 * @note If the variable is not found in the environment, an empty string is used.
 */
static int handle_variable(char *input, int start, t_ma *ma)
{
    char    *var_name;
    char    *var_value;
    int     end;

    end = start + 1;
    while (ft_isalnum(input[end]) || input[end] == '_')
        end++;
    var_name = ft_substr_g_c(input, start + 1, end - start - 1, &(ma->first_node));
    var_value = getenv(var_name);//this should be replace by the function looking in env
    handle_variable_util(var_value, start, end, ma);
    free_ntc_prior(&(ma->first_node), var_name);
    return (end - 1);
}

/**
 * @brief Handles command substitution in the input string.
 * 
 * This function processes a command substitution (starting with '$(') in the input string.
 * It extracts the content within the parentheses and creates a token of type
 * TOKEN_COMMAND_SUBSTITUTION with the extracted content.
 * 
 * @param input The input string being processed.
 * @param start The starting index of the command substitution in the input string.
 * @param ma Pointer to the main structure containing token information.
 * @return int The ending index of the processed command substitution.
 * 
 * @note Supports nested parentheses within the command substitution.
 * @note The function does not execute the command, it only tokenizes it.
 */
static int handle_command_sub(char *input, int start, t_ma *ma)
{
    int end;
    int depth;

    end = start + 1;
    depth = 1;
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
        .value = ft_substr_g_c(input, start + 2, end - start - 3, &(ma->first_node)),
        .start_pos = start,
        .end_pos = end - 1
    };
    return (end - 1);
}

/**
 * @brief Processes variables and command substitutions in the input string.
 * 
 * This function iterates through the input string, identifying and handling
 * variables (starting with '$') and command substitutions (starting with '$('). 
 * It creates appropriate tokens for each identified element.
 * 
 * @param input The input string to be processed.
 * @param start The starting index in the input string to begin processing.
 * @param ma Pointer to the main structure containing token information.
 * 
 * @note Characters not part of variables or command substitutions are tokenized as TOKEN_WORD.
 * @note This function is responsible for populating the token array in the ma structure.
 * @note The function handles nested structures by calling appropriate helper functions.
 */
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

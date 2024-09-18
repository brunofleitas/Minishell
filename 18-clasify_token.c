/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18-clasify_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:49:28 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:09:05 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Classifies a command based on its value.
 *
 * This function takes a command string and compares it against a list of 
 * known built-in shell commands. If the command matches one of the built-in 
 * commands ("echo", "cd", "pwd", "export", "unset", "env", "exit"), it returns 
 * TOKEN_BUILTIN. Otherwise, it returns TOKEN_ERROR.
 *
 * @param value The command string to classify.
 * @return t_token_type TOKEN_BUILTIN if the command is a built-in shell command,
 *         TOKEN_ERROR otherwise.
 */
t_token_type	classify_cmd(char *value)
{
	if (ft_strcmp(value, "echo") == 0 || ft_strcmp(value, "cd") == 0
		|| ft_strcmp(value, "pwd") == 0 || ft_strcmp(value, "export") == 0
		|| ft_strcmp(value, "unset") == 0 || ft_strcmp(value, "env") == 0
		|| ft_strcmp(value, "exit") == 0)
		return (TOKEN_BUILTIN);
	return (TOKEN_ERROR);
}

/**
 * @brief Classifies a given operator string into its corresponding token type.
 *
 * This function takes a string representing an operator and returns the
 * corresponding token type. The supported operators and their token types are:
 * - "<"  : TOKEN_REDIR_IN
 * - ">"  : TOKEN_REDIR_OUT
 * - ">>" : TOKEN_REDIR_APPEND
 * - "<<" : TOKEN_HEREDOC
 * - "|"  : TOKEN_PIPE
 * - "&&" : TOKEN_AND
 * - "||" : TOKEN_OR
 * - "("  : TOKEN_LPAREN
 * - ")"  : TOKEN_RPAREN
 * If the operator does not match any of the supported types, TOKEN_ERROR is 
 * returned.
 * 
 * @param value The operator string to classify.
 * @return The corresponding token type.
 */
t_token_type	classify_operator(char *value)
{
	if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(value, "&&") == 0)
		return (TOKEN_AND);
	if (ft_strcmp(value, "||") == 0)
		return (TOKEN_OR);
	if (ft_strcmp(value, "(") == 0)
		return (TOKEN_LPAREN);
	if (ft_strcmp(value, ")") == 0)
		return (TOKEN_RPAREN);
	return (TOKEN_ERROR);
}

/**
 * @brief Classifies a variable based on its value.
 *
 * This function determines the type of a variable by examining its first 
 * character. If the first character is a digit and the string length is 1, 
 * it returns TOKEN_EXIT_STATUS. If the first character is a dollar sign ('$'), 
 * it returns TOKEN_ENV_VAR. Otherwise, it returns TOKEN_ERROR.
 *
 * @param value The string value of the variable to classify.
 * @return t_token_type The type of the token.
 */
t_token_type	classify_variable(char *value)
{
	if (ft_isdigit(value[0]) && value[1] == '\0')
		return (TOKEN_EXIT_STATUS);
	if (value[0] == '$')
		return (TOKEN_ENV_VAR);
	return (TOKEN_ERROR);
}

/**
 * @brief Classifies a given string based on its surrounding quotes.
 *
 * This function checks the first and last characters of the input string
 * to determine if it is enclosed in single quotes, double quotes, or neither.
 *
 * @param value The string to classify.
 * @return The type of token based on the classification:
 *         - TOKEN_SINGLE_QUOTE if the string is enclosed in single quotes.
 *         - TOKEN_DOUBLE_QUOTE if the string is enclosed in double quotes.
 *         - TOKEN_ERROR if the string is not properly enclosed in quotes.
 */
t_token_type	classify_string(char *value)
{
	if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		return (TOKEN_DOUBLE_QUOTE);
	return (TOKEN_ERROR);
}

/**
 * @brief Classifies a given token value into its corresponding token type.
 *
 * This function attempts to classify the provided token value by checking
 * against various token types in a specific order: command, operator,
 * variable, and string. If none of these classifications match, it defaults
 * to returning TOKEN_WORD if the value is non-empty or TOKEN_ERROR otherwise.
 *
 * @param value The token value to classify.
 * @return The classified token type.
 */
t_token_type	clasify_token(char *value)
{
	int	token_type;

	token_type = classify_cmd(value);
	if (token_type != TOKEN_ERROR)
		return (TOKEN_BUILTIN);
	token_type = classify_operator(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	token_type = classify_variable(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	token_type = classify_string(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	if (ft_strlen(value) > 0 || !value)
		return (TOKEN_WORD);
	return (TOKEN_ERROR);
}

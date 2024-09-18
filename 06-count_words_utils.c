/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06-count_words_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 04:46:57 by bruno             #+#    #+#             */
/*   Updated: 2024/09/18 03:54:16 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles quoted strings in the input.
 *
 * This function processes quoted strings in the input by advancing the
 * index `i` until the closing quote is found or the end of the string
 * is reached.
 *
 * @param s The input string.
 * @param i Pointer to the current index in the input string.
 * @return int Always returns 1.
 */
int	handle_quotes(const char *s, int *i)
{
	char	quote;

	quote = s[(*i)++];
	while (s[*i] != quote && s[*i] != '\0')
		(*i)++;
	return (1);
}

/**
 * @brief Handles double operators in the input.
 *
 * This function checks for double operators (>>, <<, &&, ||) in the
 * input string and advances the index `i` if a double operator is
 * found.
 *
 * @param s The input string.
 * @param i Pointer to the current index in the input string.
 * @return int Returns 1 if a double operator is found, otherwise 0.
 */
int	handle_double_operators(const char *s, int *i)
{
	if ((s[*i] == '>' && s[*i + 1] == '>')
		|| (s[*i] == '<' && s[*i + 1] == '<')
		|| (s[*i] == '&' && s[*i + 1] == '&')
		|| (s[*i] == '|' && s[*i + 1] == '|'))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

/**
 * @brief Handles single operators and special characters in the input.
 *
 * This function checks for single operators (>, <, (, ), |) and special
 * characters ($, $?) in the input string and advances the index `i` if
 * a single operator or special character is found.
 *
 * @param s The input string.
 * @param i Pointer to the current index in the input string.
 * @return int Returns 1 if a single operator or special character is
 *             found, otherwise 0.
 */
int	handle_single_operators_and_specials(const char *s, int *i)
{
	if (s[*i] == '>'
		|| s[*i] == '<'
		|| s[*i] == '('
		|| s[*i] == ')'
		|| s[*i] == '|'
		|| (s[*i] == '$' && s[*i + 1] == '?')
		|| s[*i] == '$')
	{
		if (s[*i] == '$' && s[*i + 1] == '?')
			(*i)++;
		return (1);
	}
	return (0);
}

/**
 * @brief Handles special cases in the input.
 *
 * This function checks for special cases in the input string, such as
 * $? and digit followed by > or >>, and advances the index `i`
 * accordingly.
 *
 * @param s The input string.
 * @param i Pointer to the current index in the input string.
 * @return int Returns 1 if a special case is found, otherwise 0.
 */
int	handle_special_cases(const char *s, int *i)
{
	if (s[*i] == '$' && s[*i + 1] == '?')
	{
		(*i) += 2;
		return (1);
	}
	if (ft_isdigit(s[*i]) && s[*i + 1] == '>' && s[*i + 2] == '>')
		return (1);
	if (ft_isdigit(s[*i]) && s[*i + 1] == '>')
		return (1);
	return (0);
}

/**
 * @brief Handles token increments in the input.
 *
 * This function processes the input string to handle quotes, double
 * operators, single operators, and special characters, and increments
 * the token counter accordingly.
 *
 * @param s The input string.
 * @param i Pointer to the current index in the input string.
 * @return int The number of tokens incremented.
 */
int	handle_token_increments(const char *s, int *i)
{
	int	counter;

	counter = 0;
	if (s[*i] == '"' || s[*i] == '\'')
		counter += handle_quotes(s, i);
	else if (handle_double_operators(s, i)
		|| handle_single_operators_and_specials(s, i))
		counter++;
	return (counter);
}

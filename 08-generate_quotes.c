/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07-generate_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 06:18:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 00:34:58 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Generates a quoted string and appends it to the split array.
 *
 * Processes a quoted string from `s`, duplicates it, and appends it to
 * `split` at index `i`. Manages memory using `ma`.
 *
 * @param s Pointer to the input string pointer. Incremented as the function
 *          processes the quoted string.
 * @param split Pointer to the array of strings where the result is stored.
 * @param i Pointer to the current index in the split array. Incremented after
 *          storing the result.
 * @param ma Pointer to the memory allocator structure.
 */
void	generate_quotes(const char **s, char ***split, int *i, t_ma *ma)
{
	char	quote;
	char	*result;

	quote = **s;
	(*s)++;
	result = ft_strdup_g_c("", &(ma->first_node));
	append_char(quote, &result, ma);
	handle_quote_content(s, &result, quote, ma);
	handle_newline_if_needed(s, &result, ma);
	append_char(quote, &result, ma);
	(*split)[(*i)++] = result;
	(*s)++;
}

/**
 * @brief Appends a character to a dynamically allocated string.
 *
 * Appends the character `s` to the string pointed to by `result`.
 * The string is reallocated to fit the new character and null terminator.
 *
 * @param s The character to append.
 * @param result A pointer to the string to which the character will be appended
 * @param ma A pointer to a memory allocator structure for managing memory.
 */
void	append_char(char s, char **result, t_ma *ma)
{
	int	len;

	len = ft_strlen(*result);
	*result = ft_realloc_g_c(&(ma->first_node), *result, len + 2);
	if (*result)
	{
		(*result)[len++] = s;
		(*result)[len] = '\0';
	}
}

/**
 * @brief Handles the content within quotes during string parsing.
 *
 * This function processes the content inside a quoted string, handling 
 * special cases like consecutive quotes, environment variable expansion, 
 * and appending regular characters to the result string.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param result Pointer to the result string where processed characters 
 *               are appended.
 * @param quote Character representing the current quote context ('"' or '\'').
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and state management.
 */
void	handle_quote_content(const char **s, char **result, char quote,
	t_ma *ma)
{
	while (**s)
	{
		if (handle_double_q(s, result, quote, ma))
			continue ;
		if (handle_special(s, result, quote, ma))
			continue ;
		if (**s == quote)
			break ;
		append_char(*(*s)++, result, ma);
	}
}

/**
 * @brief Handles the insertion of a newline if certain conditions are met.
 *
 * This function checks the next characters in the string for specific 
 * conditions involving a dollar sign (`$`) and adds a newline to the result 
 * string if needed.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param result Pointer to the result string where the newline is appended.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and state management.
 */
void	handle_newline_if_needed(const char **s, char **result, t_ma *ma)
{
	if (((*(*s + 1)) && (*(*s + 1)) == '$') && ((*(*s + 2))
			|| (*(*s + 2) == ' ')))
	{
		append_char('\n', result, ma);
		(*s)++;
	}
	if (((*(*s + 1)) && (*(*s + 1)) == '$') && (*(*s + 2) == '\0'))
	{
		append_char('\n', result, ma);
		(*s)++;
	}
}

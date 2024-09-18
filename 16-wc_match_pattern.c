/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16-wc_match_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 03:45:34 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 01:36:50 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Matches a string against a pattern containing a wildcard (`*`).
 *
 * This function matches a string against a pattern that may include a 
 * wildcard (`*`). It skips over consecutive asterisks in the pattern and 
 * checks for matches by recursively comparing the remaining string and 
 * pattern. The wildcard matches any sequence of characters.
 *
 * @param str The input string to match.
 * @param pattern The pattern to match against, which may contain a `*`.
 * @return 1 if the string matches the pattern, 0 otherwise.
 */
int	match_star_pattern(const char *str, const char *pattern)
{
	while (*pattern == '*')
		pattern++;
	if (*pattern == '\0')
		return (1);
	while (*str)
	{
		if (match_pattern(str, pattern))
			return (1);
		str++;
	}
	return (0);
}

/**
 * @brief Checks if the end of a pattern has been reached.
 *
 * This function checks whether the given pattern string has reached its 
 * terminating null character, indicating the end of the pattern.
 *
 * @param pattern The pattern string to check.
 * @return 1 if the pattern has reached its end, 0 otherwise.
 */
int	is_pattern_end(const char *pattern)
{
	return (*pattern == '\0');
}

/**
 * @brief Match a string against a wildcard pattern
 *
 * This function implements a recursive algorithm to match a string against
 * a wildcard pattern. It supports '*' (match any sequence of characters)
 * and '?' (match any single character) wildcards. The function handles
 * various cases:
 * 1. End of pattern
 * 2. '*' wildcard
 * 3. End of string
 * 4. Character match or '?' wildcard
 * 5. No match
 *
 * @param str The string to match
 * @param pattern The wildcard pattern to match against
 * @return int Returns 1 if the string matches the pattern, 0 otherwise
 */
int	match_pattern(const char *str, const char *pattern)
{
	if (is_pattern_end(pattern))
		return (*str == '\0');
	if (*pattern == '*')
		return (match_star_pattern(str, pattern));
	if (*str == '\0')
		return (0);
	if (*pattern == *str)
		return (match_pattern(str + 1, pattern + 1));
	return (0);
}

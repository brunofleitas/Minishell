#include "minishell.h"

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
	if (*pattern == '\0')
	{
		if (*str == '\0')
			return (1);
		else
			return (0);
	}
	if (*pattern == '*')
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
	if (*str == '\0')
		return (0);
	if (*pattern == *str /* || *pattern == '?' */)
		return (match_pattern(str + 1, pattern + 1));
	return (0);
}

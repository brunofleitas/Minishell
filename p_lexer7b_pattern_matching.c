#include "minishell.h"

static int match_star(const char *filename, const char *pattern);
static int match_question(const char *filename, const char *pattern);
static int match_bracket(const char *filename, const char *pattern);

/**
 * @brief Matches a filename against a wildcard pattern.
 * 
 * This function supports the following wildcard patterns:
 * '*' - Matches any number of characters
 * '?' - Matches any single character
 * '[...]' - Matches any single character within the brackets
 * 
 * @param filename The filename to match.
 * @param pattern The wildcard pattern to match against.
 * @return int Returns 1 if the filename matches the pattern, 0 otherwise.
 * 
 * @note This function calls helper functions for specific pattern types.
 * @note The function is case-sensitive in its matching.
 */
int match_pattern(const char *filename, const char *pattern)
{
    while (*pattern)
    {
        if (*pattern == '*')
            return match_star(filename, pattern + 1);
        else if (*pattern == '?')
            return match_question(filename, pattern);
        else if (*pattern == '[')
            return match_bracket(filename, pattern);
        else if (*pattern != *filename)
            return 0;
        else
        {
            pattern++;
            filename++;
        }
    }
    return !*filename && !*pattern;
}

/**
 * @brief Matches a filename against a star (*) wildcard pattern.
 * 
 * This function handles the '*' wildcard, which matches any number of characters.
 * It recursively tries to match the rest of the pattern at each position in the filename.
 * 
 * @param filename The filename to match.
 * @param pattern The remainder of the pattern after the '*'.
 * @return int Returns 1 if a match is found, 0 otherwise.
 * 
 * @note This function is called by match_pattern when a '*' is encountered.
 * @note It uses recursion, which could potentially lead to stack overflow for very long filenames.
 */
static int match_star(const char *filename, const char *pattern)
{
    if (!*pattern)
        return 1;
    while (*filename)
        if (match_pattern(filename++, pattern))
            return 1;
    return 0;
}

/**
 * @brief Matches a filename against a question mark (?) wildcard pattern.
 * 
 * This function handles the '?' wildcard, which matches any single character.
 * 
 * @param filename The filename to match.
 * @param pattern The pattern including and after the '?'.
 * @return int Returns 1 if a match is found, 0 otherwise.
 * 
 * @note This function is called by match_pattern when a '?' is encountered.
 * @note It fails if the filename is empty, as '?' must match exactly one character.
 */
static int match_question(const char *filename, const char *pattern)
{
    if (!*filename)
        return 0;
    return match_pattern(filename + 1, pattern + 1);
}

/**
 * @brief Matches a filename against a bracket [...] wildcard pattern.
 * 
 * This function handles the '[...]' wildcard, which matches any single character within the brackets.
 * 
 * @param filename The filename to match.
 * @param pattern The pattern including and after the '['.
 * @return int Returns 1 if a match is found, 0 otherwise.
 * 
 * @note This function is called by match_pattern when a '[' is encountered.
 * @note It does not support character ranges (e.g., [a-z]) or negation (e.g., [!abc]).
 */
static int match_bracket(const char *filename, const char *pattern)
{
    pattern++;
    int matched = 0;
    while (*pattern && *pattern != ']')
    {
        if (*pattern == *filename)
            matched = 1;
        pattern++;
    }
    if (!matched)
        return 0;
    return match_pattern(filename + 1, pattern + 1);
}
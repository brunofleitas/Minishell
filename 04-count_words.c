/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-count_tkns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:14:54 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/11 19:48:25 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of tokens in a string.
 *
 * This function counts the number of tokens in the given string `s` 
 * separated by the character `c`. It handles special cases and token 
 * increments using helper functions `handle_special_cases` and 
 * `handle_token_increments`. The function also considers specific 
 * characters (e.g., ' ', '>', '<', '&', '(', ')', '|', '$', '?') as 
 * token separators.
 *
 * @param s The input string to be tokenized.
 * @param c The character used as a delimiter to separate tokens.
 * @return int The number of tokens in the input string.
 */
int count_tks(char const *s, char c)
{
    int counter;
    int i;

    counter = 0;
    i = 0;
    if (*s == '\0')
        return (0);
    while (s[i] != '\0')
    {
        if (handle_special_cases(s, &i))
            counter++;
        else
            counter += handle_token_increments(s, &i);
        if (s[i] != c && (i == 0 || s[i - 1] == c
                || ft_strchr(" ><&()|$?", s[i - 1])))
            counter++;
        i++;
    }
    return (counter);
}

/*
int	count_tks(char const *s, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			counter++;
			i += 2;
		}
		if (ft_isdigit(s[i]) && s[i + 1] == '>' && s[i + 2] == '>')
			counter++;
		else if (ft_isdigit(s[i]) && s[i + 1] == '>')
			counter++;
		else if (s[i] == '"' || s[i] == '\'')
			counter += handle_quotes(s, &i);
		else if (handle_double_operators(s, &i)
			|| handle_single_operators_and_specials(s, &i))
			counter++;
		else if (s[i] != c && (i == 0 || s[i - 1] == c || ft_strchr(" ><&()|$?",
					s[i - 1])))
			counter++;
		i++;
	}
	return (counter);
}
*/

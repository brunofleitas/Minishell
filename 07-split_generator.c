/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07-split_generator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:14:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 03:55:52 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Processes a character from the input string and generates the 
 * appropriate token.
 *
 * This function determines the type of the current character in the input 
 * string `s` and calls the corresponding token generation function. It 
 * handles quoted strings, double operators, single operators, special 
 * characters, and regular tokens.
 *
 * @param s Pointer to the input string.
 * @param split Pointer to the array of strings where the generated tokens 
 * will be stored.
 * @param i Pointer to the current index in the `split` array.
 * @param ma Pointer to a structure containing metadata or additional 
 * information required for token generation.
 */
void	process_char(const char **s, char ***split, int *i, t_ma *ma)
{
	if (**s == '"' || **s == '\'')
		generate_quotes(s, split, i, ma);
	else if ((**s == '>' && *(*s + 1) == '>')
		|| (**s == '<' && *(*s + 1) == '<')
		|| (**s == '&' && *(*s + 1) == '&')
		|| (**s == '|' && *(*s + 1) == '|'))
		generate_double_operators(s, split, i, ma);
	else if (**s == '>'
		|| **s == '<'
		|| **s == '('
		|| **s == ')'
		|| **s == '|'
		|| (**s == '$' && *(*s + 1) == '?')
		|| **s == '$')
		generate_single_operators_and_specials(s, split, i, ma);
	else
		generate_regular_tkns(s, split, i, ma);
}

/**
 * ft_split_tkns - Splits the input string into tokens based on a delimiter.
 * @c: The delimiter character.
 * @ma: Pointer to the t_ma structure with the input string and metadata.
 *
 * Splits the input string from the t_ma structure into tokens using the
 * specified delimiter. Returns a dynamically allocated array of strings
 * containing the tokens, or NULL on error.
 *
 * Return: Array of strings with tokens, or NULL if an error occurs.
 */
char	**ft_split_tkns(char c, t_ma *ma)
{
	char		**split;
	int			i;
	const char	*s;

	s = (const char *)ma->input;
	i = 0;
	split = g_c(&(ma->first_node), (count_tks(s, c) + 1)
			* sizeof(char *))->data;
	if (!s || !split)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
			process_char(&s, &split, &i, ma);
	}
	split[i] = NULL;
	return (split);
}

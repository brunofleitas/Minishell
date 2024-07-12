/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-split_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:14:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/11 20:02:25 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
	s: Pointer to the input string.
	split: Pointer to the array of pointers to strings (tokens).
	i: Pointer to an integer indicating the current index in the tokens array.
  Description:
	Extracts and stores a quoted word from the input string into the tokens 
	array.
	Increments the index in the tokens array and advances the input string past 
	the extracted word. Handles both single and double quotes. Adjusts the 
	advancement of the input string based on whether the quote ends at the end 
	of the line or not.
*/
static void	generate_quotes(const char **s, char ***split, int *i)
{
	char	quote;
	int		word_length;

	quote = *(*s)++;
	word_length = 0;
	while ((*s)[word_length] != quote && (*s)[word_length])
		word_length++;
	(*split)[(*i)++] = ft_substr(*s, 0, word_length);
	if ((*s)[word_length] != '\0')
		*s += word_length + 1;
	else
		*s += word_length;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tokens).
    i: Pointer to an integer indicating the current index in the tokens array.
  Description:
    Extracts and stores a double operator (e.g., '>>', '<<', '&&', '||') from 
	the input string into the tokens array. Advances the input string by 2 
	positions to skip the operator.
*/
static void	generate_double_operators(const char **s, char ***split, int *i)
{
	(*split)[(*i)++] = ft_substr(*s, 0, 2);
	*s += 2;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tokens).
    i: Pointer to an integer indicating the current index in the tokens array.
  Description:
    Extracts and stores a single operator or special character (including '$?') 
	from the input string into the tokens array. The length of the substring 
	depends on the specific operator or special character.
    Advances the input string by the length of the extracted substring.
*/
static void	generate_single_operators_and_specials(const char **s,
		char ***split, int *i)
{
	int	len;

	len = 1;
	if (**s == '$' && *(*s + 1) == '?')
		len = 2;
	(*split)[(*i)++] = ft_substr(*s, 0, len);
	*s += len;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tokens).
    i: Pointer to an integer indicating the current index in the tokens array.
  Description:
    Extracts and stores a regular token (any sequence of characters not 
	matching the specified operators or special characters) from the input 
	string into the tokens array. Calculates the length of the token by finding 
	the first occurrence of an operator or special character. Advances the 
	input string by the length of the extracted token.
*/
static void	generate_regular_tokens(const char **s, char ***split, int *i)
{
	int	word_length;

	word_length = 0;
	while ((*s)[word_length] && !strchr(" ><&()|$", (*s)[word_length]))
		word_length++;
	(*split)[(*i)++] = ft_substr(*s, 0, word_length);
	*s += word_length;
}

/*
  Parameters:
	s: Input string to be split into tokens.
	c: Character used to determine token boundaries.
  Return value:
	A pointer to an array of strings, each representing a token from the input
	string.
	Returns NULL if the input string or the allocated memory cannot be processed
  Description:
	Splits the input string into tokens based on the specified delimiter
	character.
	Handles various cases including quotes, double operators, single operators,
	and regular tokens. Allocates memory for the resulting array of tokens and
	initializes it accordingly. The last element of the array is set to NULL
	to indicate the end.
*/
char	**ft_split_tokens(char const *s, char c)
{
	char	**split;
	int		i;

	i = 0;
	split = malloc((count_words_tokens(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else if (*s == '"' || *s == '\'')
			generate_quotes(&s, &split, &i);
		else if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s
					+ 1) == '<') || (*s == '&' && *(s + 1) == '&') || (*s == '|'
				&& *(s + 1) == '|'))
			generate_double_operators(&s, &split, &i);
		else if (*s == '>' || *s == '<' || *s == '(' || *s == ')' || *s == '|'
			|| (*s == '$' && *(s + 1) == '?') || *s == '$')
			generate_single_operators_and_specials(&s, &split, &i);
		else
			generate_regular_tokens(&s, &split, &i);
	}
	split[i] = NULL;
	return (split);
}
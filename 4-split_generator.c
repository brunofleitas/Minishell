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
	split: Pointer to the array of pointers to strings (tkns).
	i: Pointer to an integer indicating the current index in the tkns array.
  Description:
	Extracts and stores a quoted word from the input string into the tkns 
	array.
	Increments the index in the tkns array and advances the input string past 
	the extracted word. Handles both single and double quotes. Adjusts the 
	advancement of the input string based on whether the quote ends at the end 
	of the line or not.
*/
static void	generate_quotes(const char **s, char ***split, int *i, t_ntc **first_node)
{
	char	quote;
	int		word_length;

	quote = *(*s)++;
	word_length = 0;
	while ((*s)[word_length] != quote && (*s)[word_length])
		word_length++;
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, word_length, first_node);
	if ((*s)[word_length] != '\0')
		*s += word_length + 1;
	else
		*s += word_length;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a double operator (e.g., '>>', '<<', '&&', '||') from 
	the input string into the tkns array. Advances the input string by 2 
	positions to skip the operator.
*/
static void	generate_double_operators(const char **s, char ***split, int *i, \
															t_ntc **first_node)
{
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, 2, first_node);
	*s += 2;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a single operator or special character (including '$?') 
	from the input string into the tkns array. The length of the substring 
	depends on the specific operator or special character.
    Advances the input string by the length of the extracted substring.
*/
static void	generate_single_operators_and_specials(const char **s,
		char ***split, int *i, t_ntc **first_node)
{
	int	len;

	len = 1;
	if (**s == '$' && *(*s + 1) == '?')
		len = 2;
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, len, first_node);
	*s += len;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a regular token (any sequence of characters not 
	matching the specified operators or special characters) from the input 
	string into the tkns array. Calculates the length of the token by finding 
	the first occurrence of an operator or special character. Advances the 
	input string by the length of the extracted token.
*/
static void	generate_regular_tkns(const char **s, char ***split, int *i, \
																t_ntc **first_node)
{
	int	word_length;

	word_length = 0;
	while ((*s)[word_length] && !strchr(" ><&()|$", (*s)[word_length]))
		word_length++;
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, word_length, first_node);
	*s += word_length;
}

/*
  Parameters:
	s: Input string to be split into tkns.
	c: Character used to determine token boundaries.
  Return value:
	A pointer to an array of strings, each representing a token from the input
	string.
	Returns NULL if the input string or the allocated memory cannot be processed
  Description:
	Splits the input string into tkns based on the specified delimiter
	character.
	Handles various cases including quotes, double operators, single operators,
	and regular tkns. Allocates memory for the resulting array of tkns and
	initializes it accordingly. The last element of the array is set to NULL
	to indicate the end.
*/
char	**ft_split_tkns(char const *s, char c, t_ntc **first_node)
{
	char	**split;
	int		i;

	i = 0;
	split = g_c(first_node, (count_w_tks(s, c) + 1) * sizeof(char *))->data;
	if (!s || !split)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else if (*s == '"' || *s == '\'')
			generate_quotes(&s, &split, &i, first_node);
		else if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s
					+ 1) == '<') || (*s == '&' && *(s + 1) == '&') || (*s == '|'
				&& *(s + 1) == '|'))
			generate_double_operators(&s, &split, &i, first_node);
		else if (*s == '>' || *s == '<' || *s == '(' || *s == ')' || *s == '|'
			|| (*s == '$' && *(s + 1) == '?') || *s == '$')
			generate_single_operators_and_specials(&s, &split, &i, first_node);
		else
			generate_regular_tkns(&s, &split, &i, first_node);
	}
	split[i] = NULL;
	return (split);
}
// f_node is an alias for first_node but I had to shorten it otherwise the funtion would have been more than 25 lines long.

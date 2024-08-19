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

/*
  Parameters:
    s: Input string.
    i: Pointer to an integer indicating the current position in the string.
  Return value:
    1 if the function successfully handles quotes, otherwise returns 0.
  Description:
    Processes quotes in the input string. Moves the position indicator forward
    until it encounters another instance of the same quote character or reaches
    the end of the string. Returns 1 upon successful completion, signaling
	readiness to continue parsing.
*/
static int	handle_quotes(const char *s, int *i)
{
	char	quote;

	quote = s[(*i)++];
	while (s[*i] != quote && s[*i] != '\0')
		(*i)++;
	return (1);
}

/*
  Parameters:
    s: Input string.
    i: Pointer to an integer indicating the current position in the string.
  Return value:
    1 if the function successfully identifies a double operator, otherwise
	returns 0.
  Description:
    Checks for occurrences of double operators ('>>', '<<', '&&', '||') in the 
	input string.
    Advances the position indicator if a double operator is found and returns 1.
    Otherwise, returns 0.
*/
static int	handle_double_operators(const char *s, int *i)
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

/*
  Parameters:
    s: Input string.
    i: Pointer to an integer indicating the current position in the string.
  Return value:
    1 if the function successfully identifies a single operator or special 
	character, otherwise returns 0.
  Description:
    Identifies single operators ('>', '<', '|') and special characters ('$') 
	in the input string.
    Specifically, it checks for the sequence '$?' and increments the position 
	indicator if found. Returns 1 upon identifying a valid character or 
	sequence, otherwise returns 0.
*/
static int	handle_single_operators_and_specials(const char *s, int *i)
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

/*
  Parameters:
    s: Input string.
    c: Character used to separate tkns.
  Return value:
    Number of tkns found in the input string.
  Description:
    Counts the number of tkns in the input string, considering various
	conditions such as quotes, double operators, single operators, and
	special characters. tkns are incremented based on whether they 
	are surrounded by the separator character or are adjacent to it but 
	not immediately preceded by it.
*/
int	count_tks(char const *s, char c)
{
	int	counter;
	int	i;

	//printf("--------------------count_tks---------------------\n");
	counter = 0; 
	i = 0;
	if (*s == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) && s[i + 1] == '>' && s[i + 2] == '>')
			counter++;
		else if (ft_isdigit(s[i]) && s[i + 1] == '>')
			counter++;
		else if (s[i] == '"' || s[i] == '\'')
			counter += handle_quotes(s, &i);
		else if (handle_double_operators(s, &i)
			|| handle_single_operators_and_specials(s, &i))
			counter++;
		else if (s[i] != c && (i == 0 || s[i - 1] == c))
			counter++;
		else if (s[i] !=c && s[i + 1] == '\0')
			counter++;
		i++;
	}
	//printf("Number of tkns: %d\n", counter);
	return (counter);
}

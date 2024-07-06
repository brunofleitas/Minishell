/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:52:49 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/06 12:20:58 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters: 
      s: The string to count words from.
      c: The delimiter character.
  Return value:
      The number of words delimited by character 'c' in the string 's'.
  Description:
      Counts the number of words in the string 's' delimited by
	  the character 'c'.
*/
static int	count_words(char const *s, char c)
{
	int	counter;
	int	i;

	i = 0;
	if (*s == '\0')
		return (0);
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
				i++;
			counter++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
			counter++;
		}
		else if (s[i] != c && (i == 0 || s[i - 1] == c))
			counter++;
		i++;
	}
	return (counter);
}

/*
  Parameters: 
      s: The string to be split.
      c: The delimiter character.
  Return value:
      An array of strings representing the words delimited by character 'c' in
	  the string 's'.
      NULL if memory allocation fails or if 's' is NULL.
  Description:
      Splits the string 's' into an array of strings, where each element 
	  represents a word
      delimited by the character 'c'. Memory is allocated dynamically for
	  the array of strings.
*/
char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word_length;
	int		i;

	i = 0;
	split = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
            if (*s == '"')
            {
                s++;
                word_length = 0;
                while (s[word_length] != '"' && s[word_length])
                    word_length++;
                split[i++] = ft_substr(s - 1, 0, word_length + 2);
                s += word_length + 1;
            }
            else if (*s == '\'')
            {
                s++;
                word_length = 0;
                while (s[word_length] != '\'' && s[word_length])
                    word_length++;
                split[i++] = ft_substr(s - 1, 0, word_length + 2);
                s += word_length + 1;
            }
            else
            {
                if (!ft_strchr(s, c))
                    word_length = ft_strlen(s);
                else
                    word_length = (int)(ft_strchr(s, c) - s);
                split[i++] = ft_substr(s, 0, word_length);
                s += word_length;
            }
		}
	}
	split[i] = NULL;
	return (split);
}

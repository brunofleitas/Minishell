/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:53:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/05 15:53:22 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters: 
      s: The string to search for leading characters to trim.
      set: The set of characters to trim from the beginning of 's'.
  Return value:
      The index of the first non-trimmed character in 's'.
  Description:
      Finds the index of the first character in 's' that is not present in
	  the set of characters 'set'.
      Returns the index of the first non-trimmed character in 's'.
*/
static size_t	find_trim_start(const char *s, const char *set)
{
	size_t	start;

	start = 0;
	while (s[start] != '\0' && ft_strchr(set, s[start]))
		start++;
	return (start);
}

/*
  Parameters: 
      s: The string to search for trailing characters to trim.
      set: The set of characters to trim from the end of 's'.
  Return value:
      The index of the last non-trimmed character in 's'.
  Description:
      Finds the index of the last character in 's' that is not present in 
	  the set of characters 'set'.
      Returns the index of the last non-trimmed character in 's'.
*/
static size_t	find_trim_end(const char *s, const char *set)
{
	size_t	end;

	end = ft_strlen(s);
	while (end > 0 && ft_strchr(set, s[end - 1]))
		end--;
	return (end);
}

/*
  Parameters: 
      s1: The string to be trimmed.
      set: The set of characters to trim from the beginning and end of 's1'.
  Return value:
      A newly allocated string containing a copy of 's1' with leading and 
	  trailing characters from 'set' removed.
      An empty string if 's1' consists solely of characters from 'set'.
      NULL if memory allocation fails or if 's1' or 'set' is NULL.
  Description:
      Creates a new string by removing leading and trailing characters 
	  from 'set' from the string 's1'.
      Returns a pointer to the newly allocated trimmed string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = find_trim_start(s1, set);
	end = find_trim_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	len = end - start;
	trimmed = malloc((len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, len + 1);
	return (trimmed);
}

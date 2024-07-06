/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:33:36 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/05 15:53:26 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters: 
      s: The string from which to create the substring.
      start: The start index of the substring in the string 's'.
      len: The maximum length of the substring.
  Return value:
      A newly allocated substring of 's', starting from index 'start' and 
	  of maximum length 'len'.
      An empty string if 'start' is greater than the length of 's'.
      NULL if memory allocation fails or if 's' is NULL.
  Description:
      Creates a new substring of 's' starting from index 'start' and 
	  of maximum length 'len'.
      Returns a pointer to the newly allocated substring.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substr = malloc(sizeof(char));
		substr[0] = 0;
		return (substr);
	}
	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

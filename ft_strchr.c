/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:04:20 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/05 15:53:09 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters: 
      s: The string to search within.
      c: The character to search for.
  Return value:
      A pointer to the first occurrence of character 'c' in the string 's'.
      NULL if 'c' is not found in 's'.
  Description:
      Searches for the first occurrence of character 'c' in the string 's'.
      Returns a pointer to the first occurrence of 'c' if found,
	  otherwise returns NULL.
*/
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if (*ptr == (char)c)
		return (ptr);
	else
		return (0);
}

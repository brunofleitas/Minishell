/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:51:53 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/05 21:51:13 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters: 
      src: The string to be duplicated.
  Return value:
      A pointer to a newly allocated string which is a duplicate 
	  of the string 'src'.
      NULL if memory allocation fails or if 'src' is NULL.
  Description:
      Allocates memory for a new string and duplicates the contents of 
	  the string 'src' into it.
      Returns a pointer to the newly allocated string.
*/
char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	dest = (char *)malloc(ft_strlen(s) + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:55:33 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/05 15:53:17 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters: 
      str: The string to calculate the length of.
  Return value:
      The length of the string 'str', excluding the terminating null byte.
  Description:
      Calculates the length of the string 'str' by counting the number 
	  of characters until the null terminator '\0' is encountered.
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

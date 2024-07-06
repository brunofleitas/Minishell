/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:15:47 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/05 15:52:58 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters: 
      dst: The destination buffer where the string will be copied to.
      src: The source string to be copied.
      size: The size of the destination buffer 'dst'.
  Return value:
      The length of the source string 'src'.
  Description:
      Copies the string 'src' into the buffer 'dst', up to 'size' - 1 bytes.
      Ensures that 'dst' is null-terminated.
      Returns the length of the source string 'src'.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (size > 0)
	{
		while (i < size - 1 && src[i] != 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (srclen);
}

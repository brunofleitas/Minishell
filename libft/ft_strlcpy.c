/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:40:51 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:57:30 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclength;

	srclength = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (srclength);
	while (i < size - 1 && src[i] != '\0' && dst)
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	return (srclength);
}

/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	char src[] = "Hello, World!";
	char dst[20];
	size_t result;

	// Case 1: Normal copy where size > length of src
	memset(dst, 'A', sizeof(dst)); // Initialize dst with 'A' for visual effect
	result = ft_strlcpy(dst, src, sizeof(dst));
	printf("After strlcpy (normal): '%s', Length tried to create: %zu\n", dst,
		result);

	// Case 2: Copy with size smaller than src
	char smallDst[5];
	memset(smallDst, 'A', sizeof(smallDst));
		// Initialize with 'A' for visual effect
	result = ft_strlcpy(smallDst, src, sizeof(smallDst));
	printf("After strlcpy (small dst): '%s', Length tried to create: %zu\n",
		smallDst, result);

	// Case 3: Size is 0, should not copy anything
	result = ft_strlcpy(dst, src, 0);
	printf("After strlcpy (size 0), Length tried to create: %zu\n", result);

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strlcpy` copies a string from `src` to `dst` up to `size` - 1 characters,
then adds a null terminator. It's designed to be safer than traditional copy
functions by avoiding buffer overflows and ensuring the destination is always
null-terminated. The function returns the length of `src`, helping you check if
the destination was large enough.
*/

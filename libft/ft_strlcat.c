/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:40:42 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:56:35 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	j = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < size)
		dst[i] = '\0';
	return (dst_len + src_len);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	char dst[20] = "Hello";
	const char *src = " World";
	size_t size;
	size_t result;

	// Case 1: Normal append within bounds
	size = sizeof(dst);
	result = ft_strlcat(dst, src, size);
	printf("After strlcat: '%s', Return: %zu\n", dst, result);

	// Case 2: Append with size less than combined length
	char dst2[20] = "Hello";
	size = 10; // Smaller than the combined length of dst2 and src
	result = ft_strlcat(dst2, src, size);
	printf("Partial append: '%s', Return: %zu\n", dst2, result);

	// Case 3: Size is 0
	char dst3[20] = "Hello";
	result = ft_strlcat(dst3, src, 0);
	printf("Size 0, no append: '%s', Return: %zu\n", dst3, result);

	// Case 4: dst size already at or beyond 'size'
	char dst4[20] = "Hello";
	result = ft_strlcat(dst4, " World", 5); // 'size' is exactly dst length
	printf("Dst size at 'size': '%s', Return: %zu\n", dst4, result);

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strlcat` appends the source string to the end of the destination string but
will only add characters up to a specified size minus one (for the null
terminator). It ensures the destination string is null-terminated and returns
the total length of the string it tried to create, which means the initial
length of `dst` plus the length of `src`. If the `size` is smaller than the
length of `dst`, it returns the length of `src` plus `size`. This function is
useful for safely concatenating strings with buffer size limits.
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:32:27 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 14:34:06 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (k < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
		k++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	const char		*str1 = "Hello, World!";
	const char		*str2 = "Hello, World!";
	const char		*str3 = "Hello, everyone!";
	unsigned char	arr1[] = {1, 2, 3, 4, 5};
	unsigned char	arr2[] = {1, 2, 3, 4, 5};
	unsigned char	arr3[] = {1, 2, 3, 2, 1};

	// Example strings for comparison
	// Example arrays for comparison
	// Comparing identical strings
	printf("Comparing '%s' and '%s' for 13 bytes: %d\n", str1, str2,
		ft_memcmp(str1, str2, 13));
	// Comparing different strings
	printf("Comparing '%s' and '%s' for 13 bytes: %d\n", str1, str3,
		ft_memcmp(str1, str3, 13));
	// Comparing identical arrays
	printf("Comparing arr1 and arr2 for 5 bytes: %d\n", ft_memcmp(arr1, arr2,
			5));
	// Comparing different arrays
	printf("Comparing arr1 and arr3 for 5 bytes: %d\n", ft_memcmp(arr1, arr3,
			5));
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_memcmp` compares two blocks of memory, byte by byte, up to a certain length
(n). If the first differing byte in the two blocks is found, it returns the
difference between the values of these bytes. If no differences are found within
the specified bytes, it returns 0, indicating the blocks are identical in that
range. This is useful for checking if two arrays or strings are the same up to a
certain point.
*/
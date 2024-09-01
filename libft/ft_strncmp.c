/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:18 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:41:22 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare two strings up to a specified number of characters.
 *
 * This function compares the first `n` characters of the strings `s1` and `s2`.
 * The comparison is done by interpreting the characters as unsigned char and
 * comparing their ASCII values.
 *
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @param n The maximum number of characters to compare.
 *
 * @return An integer greater than, equal to, or less than 0, depending on whether
 *         `s1` is greater than, equal to, or less than `s2`.
 */
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include "libft.h"
#include <stdio.h>

int	main(void) {
	// Test with identical strings
	const char *str1 = "Hello, World!";
	const char *str2 = "Hello, World!";
	printf("Test 1 (identical): %d\n", ft_strncmp(str1, str2, 13));

	// Test with strings that differ before n characters
	const char *str3 = "Hello, World!";
	const char *str4 = "Hello, world!";
	printf("Test 2 (case difference): %d\n", ft_strncmp(str3, str4, 13));

	// Test with strings that are identical up to n characters
	const char *str5 = "Hello, World!";
	const char *str6 = "Hello, World!!!";
	printf("Test 3 (identical up to n): %d\n", ft_strncmp(str5, str6, 13));

	// Test with n larger than the strings' length
	printf("Test 4 (n larger than length): %d\n", ft_strncmp(str5, str6, 20));

	// Test with n as 0
	printf("Test 5 (n is 0): %d\n", ft_strncmp(str5, str6, 0));

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strncmp` compares two strings for a specified number of characters (`n`). It
looks at each character in order to find any difference. If the characters are
the same up to `n` or until a `\0` is found in both strings, it returns 0,
meaning they're considered equal for that length. If a difference is found, it
returns the difference between the ASCII values of the first pair of different
characters. This function is useful for comparing portions of strings or doing
safe comparisons that avoid going past the end of short strings.
*/

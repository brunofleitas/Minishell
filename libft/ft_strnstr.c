/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:42:49 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:42:52 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	const char *big = "Hello, World! This is a test.";
	const char *little = "World";
	size_t n = 20; // Limit search to the first 20 characters
	char *result;

	// Case 1: Substring found within the limit
	result = ft_strnstr(big, little, n);
	if (result != NULL)
		printf("Found: '%s'\n", result);
	else
		printf("Substring '%s' not found within the first %zu characters.\n",
			little, n);

	// Case 2: Substring not found within the limit
	little = "test";
	result = ft_strnstr(big, little, n);
	if (result == NULL)
		printf("Substring '%s' not found within the first %zu characters.\n",
			little, n);

	// Case 3: Searching with an empty 'little' string
	little = "";
	result = ft_strnstr(big, little, n);
	if (result != NULL)
		printf("Empty substring found at the beginning: '%s'\n", result);

	// Case 4: 'big' string less than 'n'
	little = "a test";
	n = 50; // More than the length of 'big'
	result = ft_strnstr(big, little, n);
	if (result != NULL)
		printf("Found: '%s'\n", result);
	else
		printf("Substring '%s' not found.\n", little);

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strnstr` searches for a small string (`little`) within a larger string
(`big`) but only up to `n` characters. If it finds `little`, it returns a
pointer to the start of `little` in `big`. If `little` is empty or not found
within the first `n` characters, it behaves differently: for an empty `little`,
it returns `big`; if not found, it returns `NULL`. This function is useful for
finding substrings with a search limit.
*/
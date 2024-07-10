/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:42:02 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:42:04 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	dlen;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substr = malloc(sizeof(char));
		substr[0] = 0;
		return (substr);
	}
	dlen = ft_strlen(s + start);
	if (len > dlen)
		len = dlen;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	const char *str = "Hello, World!";
	char *substring;

	// Typical case
	substring = ft_substr(str, 7, 5); // Expected: "World"
	if (substring != NULL) {
		printf("Substring: '%s'\n", substring);
		free(substring);
	} else {
		printf("Failed to allocate memory.\n");
	}

	// 'start' beyond the string's length
	substring = ft_substr(str, 50, 5); // Expected: ""
	if (substring != NULL) {
		printf("Substring (start beyond length): '%s'\n", substring);
		free(substring);
	} else {
		printf("Failed to allocate memory.\n");
	}

	// 'len' longer than the remainder of the string
	substring = ft_substr(str, 7, 20); // Expected: "World!"
	if (substring != NULL) {
		printf("Substring (len too long): '%s'\n", substring);
		free(substring);
	} else {
		printf("Failed to allocate memory.\n");
	}

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_substr` function extracts a segment from a string, starting at a specified
index for a given length. Here's a straightforward explanation:

1. **Memory Allocation**: Allocates memory for the new string, including space
   for the desired characters and a null terminator.

2. **Starting Point**: Specifies the start index in the original string and how
   many characters to include (`len`).

3. **Copying**: Characters from the start point up to `len` are copied into the
   new string. Adjustments are made if the start is beyond the string's end or
   if `len` exceeds available characters.

4. **Result**: Returns a new string containing the specified segment of the
   original string.

5. **Memory Management**: The allocated memory for the new string must be freed
   by the caller to prevent memory leaks.

`ft_substr` efficiently extracts specific parts of a string, managing memory
allocation and ensuring proper string termination.
*/

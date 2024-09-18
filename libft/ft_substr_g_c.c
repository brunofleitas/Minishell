/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_g_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:42:02 by pcasagra          #+#    #+#             */
/*   Updated: 2024/09/17 01:31:54 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns a substring of the given string 's' starting from the specified 
 * index 'start' and with a maximum length of 'len'.
 * If 's' is NULL, returns NULL.
 * If 'start' is greater than the length of 's', returns an empty string.
 * The function allocates memory for the substring using the 'g_c' function and 
 * returns a pointer to it.
 * The 'g_c' function is used to manage memory and is passed a pointer to the 
 * first node of a linked list.
 * The 'g_c' function allocates memory for the substring based on the length of 
 * the substring plus one for the null terminator.
 * The substring is then copied from 's' to the allocated memory using
 * 'ft_strlcpy'
 *	Returns a pointer to the allocated memory containing the substring.
 *
 * @param s The string to extract the substring from.
 * @param start The starting index of the substring.
 * @param len The maximum length of the substring.
 * @param first_node A pointer to the first node of a linked list used 
 * for memory management.
 * @return A pointer to the allocated memory containing the substring, or NULL
 * if 's' is NULL or memory allocation fails.
 */
char	*ft_substr_g_c(char const *s, unsigned int start, size_t len,
	t_ntc **first_node)
{
	char	*substr;
	size_t	dlen;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substr = g_c(first_node, sizeof(char))->data;
		if (substr == NULL)
			return (NULL);
		substr[0] = 0;
		return (substr);
	}
	dlen = ft_strlen(s + start);
	if (len > dlen)
		len = dlen;
	substr = g_c(first_node, (len + 1) * sizeof(char))->data;
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
/*
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
*/
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

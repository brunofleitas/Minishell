/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:30:45 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:32:31 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicate a string and store it in a new memory location.
 * 
 * This function duplicates the string `s` and stores it in a new memory location.
 * It also updates the global variable `g_c` with the newly allocated memory block.
 * 
 * @param s The string to be duplicated.
 * @param first_node A pointer to the first node of a linked list.
 * @return char* A pointer to the newly allocated memory block containing the duplicated string.
 *         Returns NULL if memory allocation fails.
 */
char	*ft_strdup_g_c(const char *s, t_ntc **first_node)
{
	int		i;
	char	*newstr;
	char	*scop;

	i = 0;
	scop = (char *)s;
	newstr = (char *)(g_c(first_node, ft_strlen(s) + 1)->data);
	if (newstr == NULL)
		return (NULL);
	while (*scop)
	{
		newstr[i] = *scop;
		scop++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	const char *original = "Hello, World!";
	char *duplicate;

	// Test duplicating a regular string
	duplicate = ft_strdup(original);
	if (duplicate != NULL) {
		printf("Original: %s\n", original);
		printf("Duplicate: %s\n", duplicate);
	} else {
		printf("Failed to duplicate the string.\n");
	}
	free(duplicate); // Free the duplicated string

	// Test duplicating an empty string
	original = "";
	duplicate = ft_strdup(original);
	if (duplicate != NULL) {
		printf("Original (empty): '%s'\n", original);
		printf("Duplicate (empty): '%s'\n", duplicate);
	} else {
		printf("Failed to duplicate the empty string.\n");
	}
	free(duplicate); // Free the duplicated string

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strdup` makes a newstr copy of a given string. It allocates enough memory for
the copy, then duplicates the characters of the original string into this newstr
space, ensuring the copy is identical. Finally, it returns a pointer to the
start of this newstr string. It's useful when you need a separate copy of a
string to modify or preserve.
*/
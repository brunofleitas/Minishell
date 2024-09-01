/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_g_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:39:20 by pcasagra          #+#    #+#             */
/*   Updated: 2024/08/04 15:49:12 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenates two strings and returns the result.
 * 
 * @param s1 The first string to be concatenated.
 * @param s2 The second string to be concatenated.
 * @param first_node A pointer to the first node of a linked list.
 * @return The concatenated string, or NULL if either s1 or s2 is NULL.
 */
char	*ft_strjoin_g_c(char const *s1, char const *s2, t_ntc **first_node)
{
	int		s1s2len;
	char	*join;

	if (s1 && s2)
	{
		s1s2len = ft_strlen(s1) + ft_strlen(s2);
		join = g_c(first_node, \
									(s1s2len + 1) * sizeof(char))->data;
		if (!join)
			return (NULL);
		ft_strlcpy(join, s1, ft_strlen(s1) + 1);
		ft_strlcat(join, s2, s1s2len + 1);
		return (join);
	}
	else
		return (NULL);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	const char *s1 = "Hello, ";
	const char *s2 = "World!";
	char *result;

	// Join two non-empty strings
	result = ft_strjoin(s1, s2);
	if (result != NULL) {
		printf("Joined string: %s\n", result);
		free(result); // Remember to free the dynamically allocated memory
	} else {
		printf("Memory allocation failed.\n");
	}

	// Join an empty string with a non-empty string
	result = ft_strjoin("", s2);
	if (result != NULL) {
		printf("Joined string with empty s1: %s\n", result);
		free(result);
	} else {
		printf("Memory allocation failed.\n");
	}

	// Join a non-empty string with an empty string
	result = ft_strjoin(s1, "");
	if (result != NULL) {
		printf("Joined string with empty s2: %s\n", result);
		free(result);
	} else {
		printf("Memory allocation failed.\n");
	}

	// Attempt to join null pointers
	result = ft_strjoin(NULL, NULL);
	if (result == NULL) {
		printf("Correctly handled NULL inputs.\n");
	} else {
		printf("Expected NULL but received a string.\n");
		free(result);
	}

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strjoin` combines two strings into one new string. It puts the first string
and then the second string together, end to end. This new combined string is
stored in freshly allocated memory, which means you get a brand new string that
you must remember to free later to avoid memory leaks.
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:35:19 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:35:38 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*strc;

	strc = (char *)s;
	while (*strc != '\0')
	{
		if (*strc == (char)c)
			return (strc);
		strc++;
	}
	if (*strc == (char)c)
		return (strc);
	else
		return (0);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	const char *str = "Hello, World!";
	char c = 'W';
	char *result;

	// Case 1: Character is found
	result = ft_strchr(str, c);
	if (result != NULL)
		printf("Character '%c' found: %s\n", c, result);
	else
		printf("Character '%c' not found.\n", c);

	// Case 2: Character is not found
	c = 'x';
	result = ft_strchr(str, c);
	if (result == NULL)
		printf("Character '%c' not found.\n", c);
	else
		printf("Character '%c' found: %s\n", c, result);

	// Case 3: Searching for the null terminator
	c = '\0';
	result = ft_strchr(str, c);
	if (result != NULL)
		printf("Null terminator found at position: %ld\n", result - str);
	else
		printf("Null terminator not found.\n");

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strchr` looks through a string to find the first occurrence of a specified
character. If it finds the character, it returns a pointer to that spot in the
string. If the character isn't found, it returns NULL. This function is helpful
for locating a character within a string.
*/

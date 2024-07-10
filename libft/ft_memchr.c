/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:29:48 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 14:30:45 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)s++ == (unsigned char)c)
			return ((void *)s - 1);
		i++;
	}
	return (NULL);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	const char	str[] = "Example string for testing";
	int			ch;
	size_t		n;
	char		*result;

	ch = 'e';
	n = 25;
	// Test finding a character that exists within the first n bytes
	result = ft_memchr(str, ch, n);
	if (result != NULL)
		printf("Character '%c' found at position: %ld\n", ch, result - str);
	else
		printf("Character '%c' not found in the first %zu bytes.\n", ch, n);
	// Test finding a character that does not exist within the first n bytes
	ch = 'z';
	result = ft_memchr(str, ch, n);
	if (result != NULL)
		printf("Character '%c' found at position: %ld\n", ch, result - str);
	else
		printf("Character '%c' not found in the first %zu bytes.\n", ch, n);
	// Test with the search boundary (n) smaller than the string length
	n = 5;
	ch = 's';
	result = ft_memchr(str, ch, n);
	if (result != NULL)
		printf("Character '%c' found at position: %ld within first
			%zu bytes.\n", ch, result - str, n);
	else
		printf("Character '%c' not found in the first %zu bytes.\n", ch, n);
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_memchr` looks through a block of memory for a specific character. It checks
up to a certain number of bytes (n) and if it finds the character, it returns a
pointer to its location. If the character isn't found within those bytes, it
returns NULL. This function is useful for searching in arrays or strings when
you know the size of the area you want to check.
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:37 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:41:40 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*strc;

	strc = NULL;
	while (*s)
	{
		if (*s == (char)c)
			strc = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (strc);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	const char *str = "Example sentence for testing.";
	int ch = 'e';
	char *result;

	// Case 1: Character is found at the end
	result = ft_strrchr(str, ch);
	printf("Last occurrence of '%c': %s\n", ch, result ? result : "not found");

	// Case 2: Character is not in the string
	ch = 'z';
	result = ft_strrchr(str, ch);
	printf("Last occurrence of '%c': %s\n", ch, result ? result : "not found");

	// Case 3: Character is at the beginning
	ch = 'E';
	result = ft_strrchr(str, ch);
	printf("Last occurrence of '%c': %s\n", ch, result ? result : "not found");

	// Case 4: Searching for the null terminator
	ch = '\0';
	result = ft_strrchr(str, ch);
	printf("Last occurrence of null terminator: %s\n", result + 1); //
		+1 to show the effect

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strrchr` finds the last time a specific character appears in a string(last
occurence). If the character is found, it returns a pointer to its location in
the string. This is useful when you want to locate a character's final
occurrence, such as finding the last directory separator in a file path. If the
character isn't found, it returns `NULL`.
*/
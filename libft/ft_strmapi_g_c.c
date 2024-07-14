/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:42:37 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:58:22 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char), \
													t_ntc **first_node)
{
	unsigned int	i;
	char			*result;

	if (!s || !f)
		return (NULL);
	result = (char *)(g_c(first_node, \
									(ft_strlen(s) + 1) * sizeof(char))->data);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

// Function to be applied to each character of the string
char	ft_toupper(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32); // Convert to uppercase
	return (c);
}

int	main(void)
{
	const char	*str = "hello world";
	char		*modified_str;

	// Apply ft_strmapi to the string
	modified_str = ft_strmapi(str, ft_toupper);
	if (modified_str != NULL) {
		printf("Original string: %s\n", str);
		printf("Modified string: %s\n", modified_str);
		free(modified_str); // Free the memory allocated for the modified string
	} else {
		printf("Memory allocation failed.\n");
	}
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strmapi` takes a string and applies a specified function to each character
of the string. The function uses the character's index and value to produce a
new character, creating a new string with these transformed characters. This
allows for custom modifications to a string, such as changing case or encoding
characters, and returns a new string reflecting these changes.
*/
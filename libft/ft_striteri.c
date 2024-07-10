/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:37:48 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:55:16 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include "libft.h"
#include <stdio.h>

// Test function to be applied by ft_striteri
void	capitalize_if_even(unsigned int i, char *c)
{
	if (i % 2 == 0 && *c >= 'a' && *c <= 'z') {
		*c -= 32; // Convert lowercase letter to uppercase if index is even
	}
}

int	main(void)
{
	char	str[] = "hello, world!";

	// Apply ft_striteri to the string
	ft_striteri(str, capitalize_if_even);
	// Print the modified string
	printf("Modified string: %s\n", str);
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_striteri` goes through each character in a string, applying a given function
to the character. The function it applies can change the character based on its
position in the string. This is useful for modifying a string in place, like
capitalizing certain letters or encoding characters.
*/
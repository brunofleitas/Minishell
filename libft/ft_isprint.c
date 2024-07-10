/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:44:15 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:45:19 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (c);
	else
		return (0);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
int	main(void)
{
	// Test with boundary values and a sample within the range
	printf("ft_isprint(31) = %d\n", ft_isprint(31));   // Non-printable
	printf("ft_isprint(32) = %d\n", ft_isprint(32));   // Space (printable)
	printf("ft_isprint('A') = %d\n", ft_isprint('A')); // Printable character
	printf("ft_isprint(126) = %d\n", ft_isprint(126)); // '~' (printable)
	printf("ft_isprint(127) = %d\n", ft_isprint(127)); // DEL (non-printable)
	// Test with characters across the printable range
	for (int i = 32; i < 127; i++)
	{
		if (!ft_isprint(i))
		{
			printf("Character %d is not printable, but it should be.\n", i);
		}
	}
	// Test with characters outside the printable range
	if (ft_isprint(128) || ft_isprint(-1))
	{
		printf("Non-printable char are incorrectly identified as printable.\n");
	}
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_isprint` checks if a character is printable, including a space but not the
delete character. If the character can be printed (codes 32 to 126), it returns
the character. Otherwise, it returns 0. This function helps determine if a
character is visually representable.
*/
/* ************************************************************************** */
/*                          ORIGINAL IMPLEMENTATION                           */
/* ************************************************************************** */
/*
#include <ctype.h>

int	isprint(int c)
{
		return ((unsigned)c - 0x20 < 0x5f);
}

Comments to understand:
0x20 (hexadecimal) = 32 (decimal)
0x5f (hexadecimal) = 95 (decimal) = 127 - 32
*/

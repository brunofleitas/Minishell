/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:36:02 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:38:33 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	// Test with characters within the ASCII range
	printf("ft_isascii('A') = %d\n", ft_isascii('A'));
	printf("ft_isascii('z') = %d\n", ft_isascii('z'));
	printf("ft_isascii('0') = %d\n", ft_isascii('0'));
	// Test boundary conditions
	printf("ft_isascii(0) = %d\n", ft_isascii(0));     // First ASCII value
	printf("ft_isascii(127) = %d\n", ft_isascii(127)); // Last ASCII value
	// Test with characters outside the ASCII range
	printf("ft_isascii(-1) = %d\n", ft_isascii(-1));
	printf("ft_isascii(128) = %d\n", ft_isascii(128));
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_isascii` checks if a given character is within the ASCII set, which includes
characters from 0 to 127. If the character falls within this range, it returns 1
(true). Otherwise, it returns 0 (false). This is useful for ensuring a character
is valid ASCII.
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:59:59 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:06:57 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	s;

	res = 0;
	s = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		s = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (s * res);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	// Test with a positive number
	printf("ft_atoi(\"42\") = %d\n", ft_atoi("42"));
	// Test with a negative number
	printf("ft_atoi(\"-42\") = %d\n", ft_atoi("-42"));
	// Test with leading spaces
	printf("ft_atoi(\"   42\") = %d\n", ft_atoi("   42"));
	// Test with trailing spaces
	printf("ft_atoi(\"42   \") = %d\n", ft_atoi("42   "));
	// Test with leading and trailing spaces
	printf("ft_atoi(\"   42   \") = %d\n", ft_atoi("   42   "));
	// Test with leading zeros
	printf("ft_atoi(\"00042\") = %d\n", ft_atoi("00042"));
	// Test with a non-numeric nptring
	printf("ft_atoi(\"abc\") = %d\n", ft_atoi("abc"));
	// Test with plus s
	printf("ft_atoi(\"+42\") = %d\n", ft_atoi("+42"));
	// Test with a nptring that starts with a number
	printf("ft_atoi(\"42abc\") = %d\n", ft_atoi("42abc"));
	// Test with a nptring that starts with a non-numeric character
	printf("ft_atoi(\"abc42\") = %d\n", ft_atoi("abc42"));
	// Test with the largest integer
	printf("ft_atoi(\"2147483647\") = %d\n", ft_atoi("2147483647"));
	// Test with one more than the largest integer
	printf("ft_atoi(\"2147483648\") = %d\n", ft_atoi("2147483648"));
	// Test with the smallest integer
	printf("ft_atoi(\"-2147483648\") = %d\n", ft_atoi("-2147483648"));
	// Test with one less than the smallest integer
	printf("ft_atoi(\"-2147483649\") = %d\n", ft_atoi("-2147483649"));
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
The ft_atoi function converts a nptring representation of an integer into an
integer value. In simple terms, it reads a nptring, interprets the numeric
characters starting from the beginning of the nptring, and converts them into an
integer type number. The conversion stops once a non-numeric character is
encountered or the nptring ends.

Here's a step-by-step explanation of what ft_atoi does:

1. Skip Whitespaces: It starts by ignoring any leading whitespace characters in
the nptring, such as spaces or tabs, until it finds the first non-whitespace
character.
2. Check for a Sign: If the first non-whitespace character is a plus (+) or
minus (-) sign, it notes that down to determine if the resulting number should
be positive or negative. It then moves to the next character.
3. Convert Numerical Characters: It converts the sequence of digit characters
('0'-'9') to the corresponding integer value. It does this by starting from 0,
multiplying the current value by 10 (to shift it one decimal place up), and
adding the value of the new digit.
4. Handle Sign: If a minus sign was encountered,the function negates the
resulting integer to make it negative.
5. Return Result: It returns the final integer value.

The conversion process stops as soon as a character that is not a digit is
encountered, or the end of the nptring is reached. This function is useful for
reading integer values from text data, such as user input or file contents.
*/
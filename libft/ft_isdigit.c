/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:40:11 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:42:40 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	ft_isdigit(int c);

int	main(void)
{
	// Test with digits
	for (int i = '0'; i <= '9'; i++)
	{
		printf("ft_isdigit('%c') = %d\n", i, ft_isdigit(i));
	}
	// Test with uppercase letters
	for (int i = 'A'; i <= 'Z'; i++)
	{
		printf("ft_isdigit('%c') = %d\n", i, ft_isdigit(i));
	}
	// Test with lowercase letters
	for (int i = 'a'; i <= 'z'; i++)
	{
		printf("ft_isdigit('%c') = %d\n", i, ft_isdigit(i));
	}
	// Test with non-alphanumeric characters
	printf("ft_isdigit('@') = %d\n", ft_isdigit('@'));
	printf("ft_isdigit('[') = %d\n", ft_isdigit('['));
	printf("ft_isdigit('`') = %d\n", ft_isdigit('`'));
	printf("ft_isdigit('{') = %d\n", ft_isdigit('{'));
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_isdigit` checks if a character is a number between 0 and 9. If it is, the
function returns 1. Otherwise, it returns 0. This helps determine if a character
is a digit.
*/

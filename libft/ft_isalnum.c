/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:24:48 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:25:17 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	// Test with digits
	for (int i = '0'; i <= '9'; i++)
	{
		printf("ft_isalnum('%c') = %d\n", i, ft_isalnum(i));
	}
	// Test with uppercase letters
	for (int i = 'A'; i <= 'Z'; i++)
	{
		printf("ft_isalnum('%c') = %d\n", i, ft_isalnum(i));
	}
	// Test with lowercase letters
	for (int i = 'a'; i <= 'z'; i++)
	{
		printf("ft_isalnum('%c') = %d\n", i, ft_isalnum(i));
	}
	// Test with non-alphanumeric characters
	printf("ft_isalnum('@') = %d\n", ft_isalnum('@'));
	printf("ft_isalnum('[') = %d\n", ft_isalnum('['));
	printf("ft_isalnum('`') = %d\n", ft_isalnum('`'));
	printf("ft_isalnum('{') = %d\n", ft_isalnum('{'));
	printf("ft_isalnum(' ') = %d\n", ft_isalnum(' '));
	printf("ft_isalnum('!') = %d\n", ft_isalnum('!'));
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
In simple terms, ft_isalnum checks if a character is a letter ('a' or 'Z') or a
digit ('2' or '9'). If the character is a letter or digit, it returns true (1).
Otherwise, it returns false (0). This function is useful for ensuring a
character is part of the alphabet or a numerical digit.
*/

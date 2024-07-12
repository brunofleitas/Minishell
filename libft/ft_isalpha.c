/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:27:14 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:29:47 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (c);
	else
		return (0);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	int	non_alpha[] = {'0', '@', '[', '`', '{', '9', '/', '}', '~', '+'};

	// Test with uppercase letters
	for (int i = 'A'; i <= 'Z'; i++)
	{
		printf("ft_isalpha('%c') = %d\n", i, ft_isalpha(i));
	}
	// Test with lowercase letters
	for (int i = 'a'; i <= 'z'; i++)
	{
		printf("ft_isalpha('%c') = %d\n", i, ft_isalpha(i));
	}
	// Test with non-alphabetic characters
	for (int i = 0; i < sizeof(non_alpha) / sizeof(non_alpha[0]); i++)
	{
		printf("ft_isalpha('%c') = %d\n", non_alpha[i],
			ft_isalpha(non_alpha[i]));
	}
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_isalpha` checks if a character is a letter (A-Z, a-z). If yes, it returns
the character itself. If not, it returns 0. This function helps determine if a
character is part of the alphabet.
*/
/* ************************************************************************** */
/*                          ORIGINAL IMPLEMENTATION                           */
/* ************************************************************************** */
/*
#include <ctype.h>

int	isalpha(int c)
{
		return (((unsigned)c | 32) - 'a' < 26);
}
*/

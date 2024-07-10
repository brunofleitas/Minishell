/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:13:20 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:15:34 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	s = ft_memset(s, 0, n);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hello, World!";
	int		arr[5] = {1, 2, 3, 4, 5};
	double	dbls[3] = {1.1, 2.2, 3.3};
	char	test[] = "Test";
	char	partial[] = "Partial";

	// Test with a string
	printf("Before ft_bzero on string: %s\n", str);
	ft_bzero(str, sizeof(str));
	printf("After ft_bzero on string: %s\n", str);
	// Test with an integer array
	printf("Before ft_bzero on int array: %d, %d, %d, %d, %d\n", arr[0], arr[1],
		arr[2], arr[3], arr[4]);
	ft_bzero(arr, sizeof(arr));
	printf("After ft_bzero on int array: %d, %d, %d, %d, %d\n", arr[0], arr[1],
		arr[2], arr[3], arr[4]);
	// Test with a double array
	printf("Before ft_bzero on double array: %.1f, %.1f, %.1f\n", dbls[0],
		dbls[1], dbls[2]);
	ft_bzero(dbls, sizeof(dbls));
	printf("After ft_bzero on double array: %.1f, %.1f, %.1f\n", dbls[0],
		dbls[1], dbls[2]);
	// Test with zero bytes to clear
	printf("Before ft_bzero with n = 0: %s\n", test);
	ft_bzero(test, 0);
	printf("After ft_bzero with n = 0: %s\n", test);
	// Test with partial clear
	printf("Before ft_bzero with partial clear: %s\n", partial);
	ft_bzero(partial + 3, 4); // Zero out the last 4 bytes
	printf("After ft_bzero with partial clear: %s\n", partial);
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
In simple terms, the `ft_bzero` function zeroes out a block of memory.
It takes two arguments: a pointer to the start of the memory block (`s`)
and the number of bytes to zero out (`n`). When you call `ft_bzero`,
it sets the first `n` bytes of the memory area pointed to by `s` to zero.
This is useful for initializing or resetting data in memory to ensure there
 are no leftover or garbage values from previous operations.
*/

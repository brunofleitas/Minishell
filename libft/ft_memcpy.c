/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:35:04 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 14:36:15 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*dest_ptr;
	size_t	i;

	i = 0;
	dest_ptr = dest;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		*(char *)dest++ = *(char *)src++;
		i++;
	}
	return (dest_ptr);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	char	src_str[] = "Test string";
	char	dest_str[20];
	int		src_arr[] = {1, 2, 3, 4, 5};
	int		dest_arr[5];
	char	overlap_str[] = "12345";

	// Test copying a string
	ft_memcpy(dest_str, src_str, strlen(src_str) + 1); //
		+1 for the null terminator
	printf("Copied string: %s\n", dest_str);
	// Test copying an array of integers
	ft_memcpy(dest_arr, src_arr, sizeof(src_arr));
	printf("Copied array: ");
	for (size_t i = 0; i < sizeof(src_arr) / sizeof(src_arr[0]); i++) {
		printf("%d ", dest_arr[i]);
	}
	printf("\n");
	// Test with overlapping memory areas (undefined behavior,
		just for demonstration)
	ft_memcpy(overlap_str + 2, overlap_str, 3);
	printf("Overlap copy: %s\n", overlap_str);
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_memcpy` copies data from one memory area (`src`) to another (`dest`) for a
specified number of bytes (`n`). It works byte by byte, making it suitable for
any type of data. However, it doesn't check for overlapping memory areas, so
it's important to ensure `src` and `dest` do not overlap when using it.
*/
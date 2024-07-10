/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:40:32 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 14:49:46 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (s < d)
	{
		s += n;
		d += n;
		while (n--)
			*--d = *--s;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Memory can overlap!";
	char	dest[25];

	// Example of non-overlapping copy
	ft_memmove(dest, str, strlen(str) + 1); // Include the null terminator
	printf("Non-overlapping copy: %s\n", dest);
	// Example of overlapping copy - towards the beginning
	ft_memmove(str + 5, str, strlen(str) - 4);
	printf("Overlapping copy (to beginning): %s\n", str);
	// Resetting string for next example
	memcpy(str, "Memory can overlap!", 19);
	// Example of overlapping copy - towards the end
	ft_memmove(str, str + 5, strlen(str) - 4);
	printf("Overlapping copy (to end): %s\n", str);
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_memmove` safely moves data from one place to another in memory, even if
those places overlap. It carefully copies the data to ensure nothing gets
overwritten incorrectly during the process. This makes it useful for adjusting
data within the same memory area, like shifting parts of an array around.
*/

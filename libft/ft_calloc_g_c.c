/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:18:01 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:23:18 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*copretu;
	size_t	multip;

	multip = nmemb * size;
	if (nmemb != 0 && multip / nmemb != size)
		return (NULL);
	copretu = malloc(nmemb * size);
	if (!copretu)
		return (NULL);
	ft_memset(copretu, 0, nmemb * size);
	return (copretu);
}
*/
void	*ft_calloc_g_c(size_t nmemb, size_t size, t_ntc **first_node)
{
	void	*copretu;
	size_t	multip;

	multip = nmemb * size;
	if (nmemb != 0 && multip / nmemb != size)
		return (NULL);
	copretu = g_c(first_node, nmemb * size)->data;
	if (!copretu)
		return (NULL);
	ft_memset(copretu, 0, nmemb * size);
	return (copretu);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
void	print_memory(const void *mem, size_t size);

int	main(void)
{
	int		*ints;
	void	*zero_elems;
	char	*chars;
	void	*zero_size;

	// Test with normal input
	ints = ft_calloc(5, sizeof(int));
	if (ints)
	{
		printf("Allocated and initialized array of 5 ints to: ");
		print_memory(ints, 5 * sizeof(int));
		free(ints);
	}
	else
	{
		printf("Memory allocation failed\n");
	}
	// Test with zero elements
	zero_elems = ft_calloc(0, sizeof(int));
	if (zero_elems)
	{
		printf("Allocated memory for 0 elements\n");
		free(zero_elems);
	}
	else
	{
		printf("Did not allocate memory for 0 elements\n");
	}
	// Test with large number of elements
	chars = ft_calloc(1024, sizeof(char));
	if (chars)
	{
		printf("Allocated and initialized array of 1024 chars to: ");
		print_memory(chars, 1024 * sizeof(char));
		free(chars);
	}
	else
	{
		printf("Memory allocation failed\n");
	}
	// Test with zero size
	zero_size = ft_calloc(5, 0);
	if (zero_size)
	{
		printf("Allocated memory with size 0\n");
		free(zero_size);
	}
	else
	{
		printf("Did not allocate memory with size 0\n");
	}
	return (0);
}

void	print_memory(const void *mem, size_t size)
{
	const unsigned char	*p = mem;

	for (size_t i = 0; i < size; i++)
	{
		printf("%02x ", p[i]);
	}
	printf("\n");
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
The ft_calloc function is like a helper that ensures you get a clean,
empty space for your items. Imagine wanting several drawers to store socks.
ft_calloc not only secures the exact number of drawers but also makes sure
they're clean before use.

How it works:

1. Calculate total space needed by multiplying the number of items (nmemb)
   by the size of each item (size).
2. Request the total space.
3. Clean the space by setting everything to zero, ensuring it's ready for use.
4. Provide the clean space for use.

If it can't secure the requested space, or if calculations don't add up (like
asking for zero or too much space), it returns NULL. This prevents you from
ending up with a messy or unusable space.
*/

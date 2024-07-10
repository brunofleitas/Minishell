/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:19:27 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 15:27:20 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	byte_value;
	unsigned char	*byte_pointer;
	size_t			i;

	i = 0;
	byte_value = c & 0xFF;
	byte_pointer = (unsigned char *)s;
	while (i < n)
	{
		byte_pointer[i] = byte_value;
		i++;
	}
	return (s);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
		unsigned int arrft[10] = {1 , 2 , 3 , 4 , 5, 6 , 7, 8 , 9 , 10};
		unsigned int arrmem[10] = {1 , 2 , 3 , 4 , 5, 6 , 7, 8 , 9 , 10};
		char stringft[] = "hello world";
		char stringmem[] = "hello world";
		int     i;

		i = 0;
		ft_memset(arrft, -1, 4);
		ft_memset(stringft, 50, 4);
		memset(arrmem, -1, 4);
		memset(stringmem, 50, 4);
		printf("Test ft arr of int:   ");
		while (i < 10)
		{
				printf("%d  ",arrft[i]);
				i++;
		}
		i = 0;
		printf("\n\n");
		printf("Test memset arr of int:   ");
		while (i < 10)
		{
				printf("%u  ",arrmem[i]);
				i++;
		}
		printf("\n\n");
		printf("Test ft string:   %s", stringft);
		printf("\n\n");
		printf("Test memset string:   %s", stringmem);
		printf("\n\n");
		return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_memset` fills a specified area of memory with a particular byte value. It
takes a pointer to the start of the area, the value to fill with, and how many
bytes to fill. This function is often used to initialize memory or set a memory
block to a specific value before using it.
*/
/* ************************************************************************** */
/*                         FUNCTION MECANIC EXPLAINED                         */
/* ************************************************************************** */
/*
byte_value = c & 0xFF;
this line is to only extract the last significant byte in case c > 255 or c < 0.

*byte_pointer = (unsigned char*)s;
this line is to "type cast" *s, currently a pointer to void (= no definded type
yet) to a pointer to "unsigned char*". This is necessary because it is not poss
ible to deference a "void*" pointer without first casting it to a specific type
Without this cast, the compiler would not know the size of the elements that
"*s"  is supposed to point to and thus,  it would not be able to perform the ne
cessary memory operations	correctly(it wouldn't be able to compute the next adr
ess to deference when doing byte_pointer[i])
*/

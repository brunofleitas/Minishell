/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:46:24 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 11:58:39 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intsize(long long newn, int sign)
{
	int	i;

	i = 0;
	while ((newn / 10) != 0)
	{
		newn /= 10;
		i++;
	}
	if (newn < 10)
		i++;
	if (sign)
		i++;
	return (i);
}

static void	populate(char *newstr, long long newn, int sign, int size)
{
	int	i;

	i = size - 1;
	if (sign)
		newstr[0] = '-';
	while ((newn / 10) != 0)
	{
		newstr[i] = (newn % 10) + '0';
		newn /= 10;
		i--;
	}
	newstr[i] = (newn % 10) + '0';
	newstr[size] = '\0';
}

char	*ft_itoa_gb(int n, t_ntc **first_node)
{
	int			sign;
	int			size;
	long long	newn;
	char		*newstr;

	sign = 0;
	newn = n;
	if (newn < 0)
	{
		newn = -newn;
		sign = -1;
	}
	size = ft_intsize(newn, sign);
	newstr = g_c(first_node, (size + 1) * sizeof(char))->data;
	if (!newstr)
		return (NULL);
	populate(newstr, newn, sign, size);
	return (newstr);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void)
{
	char	*result;

	// Test positive number
	result = ft_itoa(123);
	printf("ft_itoa(123) = %s\n", result);
	free(result);
	// Test negative number
	result = ft_itoa(-123);
	printf("ft_itoa(-123) = %s\n", result);
	free(result);
	// Test zero
	result = ft_itoa(0);
	printf("ft_itoa(0) = %s\n", result);
	free(result);
	// Test INT_MAX
	result = ft_itoa(2147483647);
	printf("ft_itoa(INT_MAX) = %s\n", result);
	free(result);
	// Test INT_MIN
	result = ft_itoa(-2147483648);
	printf("ft_itoa(INT_MIN) = %s\n", result);
	free(result);
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_itoa` takes an integer and converts it into a string. It's useful for
printing numbers as text or storing numeric data in string format. It handles
positive and negative numbers, turning them into their string representation,
like converting 123 to "123".
*/
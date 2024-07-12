/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:42:14 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:57:49 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	int	up;

	if (c >= 'a' && c <= 'z')
	{
		up = c - 32;
		return (up);
	}
	else
		return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_toupper('_'));
	printf("%c\n", (char)ft_toupper('_'));
}
*/

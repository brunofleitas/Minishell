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
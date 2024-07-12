/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_store_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:07:22 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/05 19:07:25 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                               STORE PRECISION                              */
/* ************************************************************************** */
int	store_precision(t_c_data *data)
{
	int	digit;

	if (*(data->s) == '.')
	{
		(data->s)++;
		digit = 0;
		if (ft_isdigit(*(data->s)))
		{
			while (ft_isdigit(*(data->s)))
			{
				digit = digit * 10 + (*(data->s) - '0');
				(data->s)++;
			}
		}
		data->str_format.precision = digit;
		return (1);
	}
	else
		return (0);
}

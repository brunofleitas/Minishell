/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substring_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:16:09 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 16:16:10 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                               SUBSTRING CREATION                           */
/* ************************************************************************** */

/* ***********************  Compute based on specifier  ********************* */

int	compute_substring(t_c_data *data)
{
	if (data->str_format.specifier == 'c')
	{
		data->rva.int_a = va_arg(data->arg_pointer, int);
		return (c_format(data));
	}
	else if (data->str_format.specifier == 's')
	{
		data->rva.void_a = va_arg(data->arg_pointer, void *);
		s_format(data);
	}
	else if (data->str_format.specifier == 'p')
	{
		data->rva.void_a = va_arg(data->arg_pointer, void *);
		if (data->rva.void_a == NULL)
			s_format(data);
		else
			n_format(data);
	}
	else
	{
		data->rva.int_a = va_arg(data->arg_pointer, int);
		n_format(data);
	}
	init_rva(data);
	return (1);
}
/*
for 'c' the impacting format are: [-][width]

for 's' the impacting format are: [-][width][precision]
*/

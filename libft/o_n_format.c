/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_n_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:19:09 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 17:02:47 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                               SUBSTRING CREATION                           */
/* ************************************************************************** */

/* ************  Turning diuXXp input into a string of characters  ********** */

static void	diuxxp_format(t_c_data *data)
{
	if (data->str_format.specifier == 'x'
		|| data->str_format.specifier == 'X'
		|| data->str_format.specifier == 'p')
		data->str_format.base = BASE_HEX_16;
	if (data->str_format.specifier == 'u'
		|| data->str_format.specifier == 'x'
		|| data->str_format.specifier == 'X'
		|| data->str_format.specifier == 'p')
		mini_itoa(data, 1);
	else
		mini_itoa(data, -1);
}
/*
mini_itoa fills the buffer format_abs with the conversion of the signed or
unsigned integer entered as an argument, into a string of characters.
*/

/* ****************  Promote and store argument into Union  ***************** */

void	n_format(t_c_data *data)
{
	if (data->str_format.specifier == 'd'
		|| data->str_format.specifier == 'i')
	{
		data->uni.s_ll = data->rva.int_a;
		if (data->uni.s_ll < 0)
		{
			data->rva.a_s = 1;
			data->uni.s_ll = -(data->uni.s_ll);
		}
	}
	else
	{
		if (data->str_format.specifier == 'u'
			|| data->str_format.specifier == 'x'
			|| data->str_format.specifier == 'X')
			data->uni.us_ll = (unsigned long long)data->rva.int_a;
		if (data->str_format.specifier == 'p')
			data->uni.us_ll = (unsigned long long)data->rva.void_a;
	}
	diuxxp_format(data);
	handle_all_n(data);
	flush_format_abs(data);
}

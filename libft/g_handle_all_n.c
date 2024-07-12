/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_handle_all_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:03:09 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/13 14:03:26 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*           APPLYING FORMAT TO FORMAT_ABS AND FILLING FORMAT_SUBSTR          */
/* ************************************************************************** */

static void	handle_precision(t_c_data *data)
{
	t_struc	ts;

	init_clean_format_num_struct(&ts);
	ts.zero_pad = data->str_format.precision - (data->len_abs - data->rva.a_s);
	if (ts.zero_pad < 0)
		ts.zero_pad = 0;
	if (data->str_format.width > data->str_format.precision)
	{
		if (ts.zero_pad != 0)
			calculate_width_pad(data, &ts, 0);
		else
			calculate_width_pad(data, &ts, 1);
	}
	if (data->str_format.specifier == 'd' || data->str_format.specifier == 'i')
		h_precision_signed(data, &ts);
	else
		h_precision_unsigned(data, &ts);
}

static void	handle_width(t_c_data *data)
{
	t_struc	ts;

	init_clean_format_num_struct(&ts);
	calculate_width_pad(data, &ts, 1);
	if (data->str_format.specifier == 'd' || data->str_format.specifier == 'i')
		h_width_signed(data, &ts);
	else
		h_width_unsigned(data, &ts);
}

static void	handle_only_flags(t_c_data *data)
{
	t_struc	ts;

	init_clean_format_num_struct(&ts);
	if (data->str_format.specifier == 'd' || data->str_format.specifier == 'i')
		h_only_flags_signed(data, &ts);
	else
		h_only_flags_unsigned(data, &ts);
}

void	handle_all_n(t_c_data *data)
{
	if (data->str_format.precision >= 0)
	{
		handle_precision(data);
		return ;
	}
	if (data->str_format.width > data->len_abs)
	{
		handle_width(data);
		return ;
	}
	handle_only_flags(data);
}
/*
if (data->str_format.precision >= 0)
	{
		if (!o_preci_o_arg(data))
		{
			if (data->format_abs[0] == '-')
				m = 1;
			if (data->str_format.precision > (data->len_abs - m))
			{
				handle_precision(data, m);
				return ;
			}
		}
		else
			return ;
	}
*/

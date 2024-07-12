/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_handle_precision_s_us.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:31:59 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/13 20:32:00 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                    ALL SUB-FUNCTIONS OF HANDLE_PRECISION                   */
/* ************************************************************************** */

void	h_precision_signed(t_c_data *data, t_struc *ts)
{
	if (!ts->width_pad)
	{
		if (!prefix_plus_minus(data, ts))
			prefix_space(data, ts);
		pad_zero_precision(data, ts);
		abs_to_substr(data, ts);
	}
	else
	{
		if (data->str_format.minus == FALSE)
			pad_space_or_zero_width(data, ts, 0);
		prefix_plus_minus(data, ts);
		pad_zero_precision(data, ts);
		abs_to_substr(data, ts);
		if (data->str_format.minus == TRUE)
			pad_space_or_zero_width(data, ts, 0);
	}
}

void	h_precision_unsigned(t_c_data *data, t_struc *ts)
{
	if (!ts->width_pad)
	{
		if (data->str_format.specifier == 'p')
		{
			if (!prefix_plus_minus(data, ts))
				prefix_space(data, ts);
		}
		else
			prefix_space(data, ts);
		prefix_ox(data, ts);
		pad_zero_precision(data, ts);
		abs_to_substr(data, ts);
	}
	else
	{
		if (data->str_format.minus == FALSE)
			pad_space_or_zero_width(data, ts, 0);
		if (data->str_format.specifier == 'p')
			prefix_plus_minus(data, ts);
		prefix_ox(data, ts);
		pad_zero_precision(data, ts);
		abs_to_substr(data, ts);
		if (data->str_format.minus == TRUE)
			pad_space_or_zero_width(data, ts, 0);
	}
}

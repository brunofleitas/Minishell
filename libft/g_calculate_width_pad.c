/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_calculate_width_pad.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:25:00 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 16:25:01 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	adjust_width_pad(t_c_data *data, t_struc *ts)
{
	if (data->str_format.specifier != 'u' && ((data->str_format.dash == TRUE
				&& data->uni.us_ll != 0) || data->str_format.specifier == 'p'))
		ts->width_pad += -2;
	if (data->format_abs[0] != '-' && data->str_format.plus == TRUE
		&& ft_strchr("pdi", data->str_format.specifier))
		ts->width_pad += -1;
	if (ts->width_pad < 0)
		ts->width_pad = 0;
}

void	calculate_width_pad(t_c_data *data, t_struc *ts, int c)
{
	if (c == 0)
	{
		ts->width_pad = data->str_format.width - data->str_format.precision
			- data->rva.a_s;
		adjust_width_pad(data, ts);
	}
	if (c == 1)
	{
		if (data->uni.us_ll == 0 && data->str_format.precision == 0)
			ts->width_pad = data->str_format.width - (data->len_abs - 1);
		else
			ts->width_pad = data->str_format.width - data->len_abs
				/*- data->rva.a_s*/;
		adjust_width_pad(data, ts);
	}
}

/*
c == 0 implies that :
data->str_format.precision >= 0
&& data->str_format.precision > data->len_abs
&& data->str_format.width > data->str_format.precision

c == 1 implies that :
ts->zero_pad == 0 || no precision
data->str_format.width > data->len_abs
*/

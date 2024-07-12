/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_s_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:19:29 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/13 09:19:31 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                               SUBSTRING CREATION                           */
/* ************************************************************************** */

/* ****************************  Specifier 's'  ***************************** */

static void	fill_ts(t_c_data *data, t_st_s *ts)
{
	if (ts->s_len == 0)
	{
		ts->truncate = 0;
		ts->width_pad = data->str_format.width;
	}
	else
	{
		if (data->str_format.precision > ts->s_len)
		{
			ts->truncate = ts->s_len;
			ts->width_pad = data->str_format.width - ts->s_len;
		}
		else
		{
			ts->truncate = data->str_format.precision;
			if (ts->truncate < data->str_format.width)
				ts->width_pad = data->str_format.width - ts->truncate;
			else
				ts->width_pad = 0;
		}
		if (ts->width_pad < 0)
			ts->width_pad = 0;
	}
}

static void	handle_precision_s(t_c_data *data, t_st_s *ts)
{
	fill_ts(data, ts);
	if (!ts->width_pad)
	{
		truncate_precision(data, ts);
	}
	else
	{
		if (data->str_format.minus == FALSE)
		{
			pad_width(data, ts);
			truncate_precision(data, ts);
		}
		if (data->str_format.minus == TRUE)
		{
			truncate_precision(data, ts);
			pad_width(data, ts);
		}
	}
}

static void	handle_width_s(t_c_data *data, t_st_s *ts)
{
	ts->width_pad = data->str_format.width - ts->s_len;
	if (data->str_format.minus == FALSE)
	{
		pad_width(data, ts);
		no_truncate(data, ts);
	}
	if (data->str_format.minus == TRUE)
	{
		no_truncate(data, ts);
		pad_width(data, ts);
	}
}

static void	handle_all_s(t_c_data *data, t_st_s *ts)
{
	if (data->str_format.precision >= 0)
	{
		if (arg_null_and_precision_less_six(data, ts))
			return ;
		handle_precision_s(data, ts);
		return ;
	}
	if (data->str_format.width > ts->s_len)
	{
		handle_width_s(data, ts);
		return ;
	}
	no_truncate(data, ts);
}

void	s_format(t_c_data *data)
{
	t_st_s	ts;

	ts.arg_null = 0;
	init_clean_format_s_struct(&ts);
	data->rva.char_a = (char *)data->rva.void_a;
	if ((data->rva.char_a == 0 || data->rva.char_a == NULL)
		&& data->str_format.specifier == 's')
	{
		data->rva.char_a = "(null)";
		ts.arg_null = 1;
	}
	if ((data->rva.char_a == 0 || data->rva.char_a == NULL)
		&& data->str_format.specifier == 'p')
		data->rva.char_a = "(nil)";
	ts.s_len = ft_strlen(data->rva.char_a);
	handle_all_s(data, &ts);
}

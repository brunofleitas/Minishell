/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_s_to_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:06:07 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/22 11:07:35 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	arg_null_and_precision_less_six(t_c_data *data, t_st_s *ts)
{
	if (data->str_format.precision >= 0 && data->str_format.precision < 6
		&& ts->arg_null == 1)
	{
		if (data->str_format.width < 1)
			return (1);
		if (data->str_format.width >= 1)
		{
			ft_memset(data->format_substr, ' ', data->str_format.width);
			return (1);
		}
	}
	return (0);
}

void	no_truncate(t_c_data *data, t_st_s *ts)
{
	int	i;

	i = 0;
	while (ts->s + ts->s_len > SIZE_BUFFER - 1)
	{
		ft_memcpy(data->format_substr + ts->s, data->rva.char_a + i, \
							(SIZE_BUFFER - 1) - ts->s);
		i += (SIZE_BUFFER - 1) - ts->s;
		ts->s_len -= ((SIZE_BUFFER - 1) - ts->s);
		ts->s += ((SIZE_BUFFER - 1) - ts->s);
		flush_format_substr_s(data, ts);
	}
	if (data->i_buffer + ts->s_len > SIZE_BUFFER - 1)
		flush_ot_buffer(data);
	ft_memcpy(data->format_substr + ts->s, data->rva.char_a + i, ts->s_len);
	ts->s += ts->s_len;
}

void	truncate_precision(t_c_data *data, t_st_s *ts)
{
	int	i;

	i = 0;
	while (ts->s + ts->truncate > SIZE_BUFFER - 1)
	{
		ft_memcpy(data->format_substr + ts->s, data->rva.char_a + i, \
							(SIZE_BUFFER - 1) - ts->s);
		i += (SIZE_BUFFER - 1) - ts->s;
		ts->truncate -= ((SIZE_BUFFER - 1) - ts->s);
		ts->s += ((SIZE_BUFFER - 1) - ts->s);
		flush_format_substr_s(data, ts);
	}
	if (data->i_buffer + ts->truncate > SIZE_BUFFER - 1)
		flush_ot_buffer(data);
	ft_memcpy(data->format_substr + ts->s, data->rva.char_a + i, ts->truncate);
	ts->s += ts->truncate;
}

void	pad_width(t_c_data *data, t_st_s *ts)
{
	while (ts->s + ts->width_pad > SIZE_BUFFER - 1)
	{
		ft_memset(data->format_substr + ts->s, ' ', (SIZE_BUFFER - 1) - ts->s);
		ts->width_pad -= ((SIZE_BUFFER - 1) - ts->s);
		ts->s += ((SIZE_BUFFER - 1) - ts->s);
		flush_format_substr_s(data, ts);
	}
	if (data->i_buffer + ts->width_pad > SIZE_BUFFER - 1)
		flush_ot_buffer(data);
	ft_memset(data->format_substr + ts->s, ' ', ts->width_pad);
	ts->s += ts->width_pad;
}

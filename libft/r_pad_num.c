/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pad_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:33:17 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/22 10:56:27 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                 ALL FORMATING PADDING-FUNCTIONS FOR NUMBERS                */
/* ************************************************************************** */

static void	protected_fill_buffer(t_c_data *data, t_struc *ts,
							char par_y, int par_z)
{
	while (ts->s + par_z > SIZE_BUFFER - 1)
	{
		ft_memset(data->format_substr + ts->s, par_y, \
						(SIZE_BUFFER - 1) - ts->s);
		par_z -= ((SIZE_BUFFER - 1) - ts->s);
		ts->s += ((SIZE_BUFFER - 1) - ts->s);
		flush_format_substr_else(data, ts);
	}
	if (data->i_buffer + par_z > SIZE_BUFFER - 1)
		flush_ot_buffer(data);
	ft_memset(data->format_substr + ts->s, par_y, par_z);
	ts->s += par_z;
}

void	pad_zero_precision(t_c_data *data, t_struc *ts)
{
	protected_fill_buffer(data, ts, '0', ts->zero_pad);
}

void	pad_space_or_zero_width(t_c_data *data, t_struc *ts, int c)
{
	if (c == 0)
		protected_fill_buffer(data, ts, ' ', ts->width_pad);
	if (c == 1)
		protected_fill_buffer(data, ts, '0', ts->width_pad);
}

/*
par_y: char space or zero
par_z: ts->zero_pad or ts->width_pad
*/
/*
Old Code
void	pad_zero_precision(t_c_data *data, t_struc *ts)
{
	ft_memset(data->format_substr + ts->s, '0', ts->zero_pad);
	ts->s += ts->zero_pad;
}

void	pad_space_or_zero_width(t_c_data *data, t_struc *ts, int c)
{
	if (c == 0)
	{
		ft_memset(data->format_substr + ts->s, ' ', ts->width_pad);
		ts->s += ts->width_pad;
		return ;
	}
	if (c == 1)
	{
		ft_memset(data->format_substr + ts->s, '0', ts->width_pad);
		ts->s += ts->width_pad;
		return ;
	}
}
*/

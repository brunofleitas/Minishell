/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_prefix_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:09 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/22 11:03:45 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                 ALL FORMATING PREFIX-FUNCTIONS FOR NUMBERS                 */
/* ************************************************************************** */

int	prefix_plus_minus(t_c_data *data, t_struc *ts)
{
	if (data->format_abs[0] == '-')
	{
		if (ts->s + 1 >= SIZE_BUFFER - 1)
			flush_format_substr_else(data, ts);
		ft_memcpy(data->format_substr + ts->s, data->format_abs, 1);
		ts->s += 1;
		ts->m += 1;
		return (TRUE);
	}
	if (data->str_format.plus == TRUE)
	{
		if (ts->s + 1 >= SIZE_BUFFER - 1)
			flush_format_substr_else(data, ts);
		ft_memcpy(data->format_substr + ts->s, "+", 1);
		ts->s += 1;
		return (TRUE);
	}
	return (FALSE);
}

void	prefix_space(t_c_data *data, t_struc *ts)
{
	if (data->str_format.space == TRUE)
	{
		if (ts->s + 1 >= SIZE_BUFFER - 1)
			flush_format_substr_else(data, ts);
		ft_memcpy(data->format_substr + ts->s, " ", 1);
		ts->s += 1;
	}
}

static int	ox_exceptions(t_c_data *data)
{
	if ((data->str_format.specifier == 'x' || data->str_format.specifier == 'X')
		&& data->uni.us_int == 0)
		return (1);
	return (0);
}

void	prefix_ox(t_c_data *data, t_struc *ts)
{
	if (data->str_format.specifier != 'u' && (data->str_format.dash == TRUE
			|| data->str_format.specifier == 'p'))
	{
		if (!ox_exceptions(data))
		{
			if (ts->s + 2 >= SIZE_BUFFER - 1)
				flush_format_substr_else(data, ts);
			ft_memcpy(data->format_substr + ts->s, "0x", 2);
			ts->s += 2;
			if (data->str_format.uppercase == TRUE)
				data->format_substr[ts->s - 1] = 'X';
		}
	}
}
/*
static void protected_fill_buffer(t_c_data *data, t_struc *ts, char par_y,
						\ int par_z)
{
	while ((ts->s < SIZE_BUFFER - 1) && (ts->s + par_z > SIZE_BUFFER - 1))
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
*/

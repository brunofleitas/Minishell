/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_handle_width_s_us.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:37:32 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/14 14:37:36 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                    ALL SUB-FUNCTIONS OF HANDLE_PRECISION                   */
/* ************************************************************************** */

void	h_width_signed(t_c_data *data, t_struc *ts)
{
	if (data->str_format.minus == FALSE)
	{
		if (data->str_format.zero == FALSE)
			pad_space_or_zero_width(data, ts, 0);
		prefix_plus_minus(data, ts);
		if (data->str_format.zero == TRUE)
			pad_space_or_zero_width(data, ts, 1);
		abs_to_substr(data, ts);
	}
	else
	{
		prefix_plus_minus(data, ts);
		abs_to_substr(data, ts);
		pad_space_or_zero_width(data, ts, 0);
	}
}

void	h_width_unsigned(t_c_data *data, t_struc *ts)
{
	if (data->str_format.minus == FALSE)
	{
		if (data->str_format.zero == FALSE)
			pad_space_or_zero_width(data, ts, 0);
		if (data->str_format.specifier == 'p')
			prefix_plus_minus(data, ts);
		prefix_ox(data, ts);
		if (data->str_format.zero == TRUE)
			pad_space_or_zero_width(data, ts, 1);
		abs_to_substr(data, ts);
	}
	else
	{
		if (data->str_format.specifier == 'p')
			prefix_plus_minus(data, ts);
		prefix_ox(data, ts);
		abs_to_substr(data, ts);
		pad_space_or_zero_width(data, ts, 0);
	}
}

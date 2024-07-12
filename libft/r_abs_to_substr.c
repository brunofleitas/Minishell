/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_abs_to_substr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:11:09 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 16:11:11 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*               TO HANDLE SPECIAL CASE OF PRECISION AND ARGUMENT 0           */
/* ************************************************************************** */

static int	o_preci_o_arg(t_c_data *data)
{
	if (data->str_format.specifier != 'p' && data->str_format.precision == 0
		&& data->uni.us_ll == 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*               FUNCTION TO FILL FORMAT_SUBSTR WITH FORMAT_ABS               */
/* ************************************************************************** */

void	abs_to_substr(t_c_data *data, t_struc *ts)
{
	if (!o_preci_o_arg(data))
	{
		ft_memcpy(data->format_substr + ts->s, data->format_abs + ts->m,
			data->len_abs - ts->m);
		ts->s += data->len_abs - ts->m;
	}
}

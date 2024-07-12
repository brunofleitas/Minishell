/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:11:58 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 16:56:48 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                                  FT_PRINTF                                 */
/* ************************************************************************** */
int	ft_printf(const char *str_tob_frmt, ...)
{
	t_c_data	data;

	va_start(data.arg_pointer, str_tob_frmt);
	if (!init_data(&data, str_tob_frmt))
		return (ERROR_CREATING_A_BUFFER);
	if (*data.s)
	{
		if (construct_ot_string(&data) == OK)
		{
			flush_ot_buffer(&data);
		}
	}
	free(data.ot_buffer);
	free(data.format_substr);
	free(data.format_abs);
	va_end(data.arg_pointer);
	return (data.r_value);
}

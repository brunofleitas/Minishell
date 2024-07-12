/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_handle_only_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:43 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/15 14:52:45 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                    ALL SUB-FUNCTIONS OF HANDLE_PRECISION                   */
/* ************************************************************************** */

void	h_only_flags_signed(t_c_data *data, t_struc *ts)
{
	if (!prefix_plus_minus(data, ts))
		prefix_space(data, ts);
	abs_to_substr(data, ts);
}

void	h_only_flags_unsigned(t_c_data *data, t_struc *ts)
{
	if (data->str_format.specifier == 'p')
	{
		if (!prefix_plus_minus(data, ts))
			prefix_space(data, ts);
	}
	prefix_space(data, ts);
	prefix_ox(data, ts);
	abs_to_substr(data, ts);
}

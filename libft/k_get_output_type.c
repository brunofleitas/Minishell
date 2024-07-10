/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_get_output_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:09:09 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 16:09:11 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	get_output_type(t_c_data *data)
{
	if (data->str_format.specifier == 'u')
		return (data->uni.us_int);
	if (data->str_format.specifier == 'p')
		return (data->uni.us_ll);
	if (data->str_format.specifier == 'd' || data->str_format.specifier == 'i')
		return (data->uni.s_ll);
	if (data->str_format.specifier == 'x' || data->str_format.specifier == 'X')
		return (data->uni.us_int);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_c_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:19:19 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/13 09:19:21 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                               SUBSTRING CREATION                           */
/* ************************************************************************** */

/* ****************************  Specifier 'c'  ***************************** */

int	c_format(t_c_data *data)
{
	if (data->str_format.width > 1)
	{
		if (data->str_format.minus == TRUE)
		{
			data->format_substr[0] = data->rva.int_a;
			ft_memset(data->format_substr + 1, ' ', data->str_format.width - 1);
		}
		else
		{
			ft_memset(data->format_substr, ' ', data->str_format.width - 1);
			data->format_substr[data->str_format.width - 1] = data->rva.int_a;
		}
		return (data->str_format.width);
	}
	else
		data->format_substr[0] = data->rva.int_a;
	return (1);
}

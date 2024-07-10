/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_extract_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:30 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 16:05:31 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                               EXTRACT FORMAT                               */
/* ************************************************************************** */
int	extract_format(t_c_data *data)
{
	if (*data->s)
	{
		store_flag(data);
		store_width(data);
		store_precision(data);
		if (store_specifier(data))
			return (OK);
	}
	return (ERROR_INCORECT_INPUT_FORMAT);
}

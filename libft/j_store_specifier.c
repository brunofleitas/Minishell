/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_store_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:07:22 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/18 16:07:24 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                               STORE SPECIFIER                              */
/* ************************************************************************** */
static void	store_specifier_base(t_c_data *data)
{
	if (data->str_format.specifier == 'd' || data->str_format.specifier == 'i'
		|| data->str_format.specifier == 'u')
		return ;
	if (data->str_format.specifier == 'p' || data->str_format.specifier == 'x'
		|| data->str_format.specifier == 'X')
		data->str_format.base = BASE_HEX_16;
	return ;
}

static void	store_specifier_uppercase(t_c_data *data)
{
	if (data->str_format.specifier == 'X')
		data->str_format.uppercase = TRUE;
	return ;
}

int	store_specifier(t_c_data *data)
{
	char	*flag;

	flag = ft_strchr("cspdiuxX%", (int)*(data->s));
	if (flag && *(data->s) != 0)
	{
		data->str_format.specifier = *flag;
		store_specifier_base(data);
		store_specifier_uppercase(data);
		(data->s)++;
		return (1);
	}
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_store_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:07:43 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/05 19:07:46 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                                 STORE FLAGS                                */
/* ************************************************************************** */
static void	toggle_flag(t_c_data *data)
{
	if (*(data->s) == '+' && data->str_format.plus == FALSE)
		data->str_format.plus = TRUE;
	if (*(data->s) == '-' && data->str_format.minus == FALSE)
		data->str_format.minus = TRUE;
	if (*(data->s) == ' ' && data->str_format.space == FALSE)
		data->str_format.space = TRUE;
	if (*(data->s) == '0' && data->str_format.zero == FALSE)
		data->str_format.zero = TRUE;
	if (*(data->s) == '#' && data->str_format.dash == FALSE)
		data->str_format.dash = TRUE;
}

int	store_flag(t_c_data *data)
{
	char	*flag;

	flag = ft_strchr("+- 0#", (int)*(data->s));
	if (flag && *(data->s) != 0)
	{
		while (flag)
		{
			toggle_flag(data);
			(data->s)++;
			flag = ft_strchr("+- 0#", (int)*(data->s));
		}
		return (FLAG_STORED);
	}
	return (NO_FLAGS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ot_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:54:07 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/22 11:24:38 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                              FILLING OT_BUFFER                             */
/* ************************************************************************** */
static void	populate_ot_buffer_w_format(t_c_data *data)
{
	int	j;

	j = 0;
	while (j < data->len_substr)
	{
		data->ot_buffer[data->i_buffer] = data->format_substr[j];
		data->i_buffer++;
		j++;
	}
}

static int	get_format(t_c_data *data)
{
	if (extract_format(data) == OK)
	{
		if (data->str_format.specifier == '%')
		{
			data->format_substr[0] = '%';
			data->len_substr = ft_strlen(data->format_substr);
		}
		else if (data->str_format.specifier == 'c')
			data->len_substr = compute_substring(data);
		else
		{
			compute_substring(data);
			data->len_substr = ft_strlen(data->format_substr);
		}
		init_clean_format_struct(data);
	}
	else
		return (ERROR_INCORECT_INPUT_FORMAT);
	if ((SIZE_BUFFER - 1) - (data->i_buffer) < data->len_substr)
		flush_ot_buffer(data);
	else
		populate_ot_buffer_w_format(data);
	empty_format_substr(data);
	return (OK);
}

static void	fill(t_c_data *data, int cas)
{
	if (!cas)
	{
		while (data->cp < data->s)
		{
			data->ot_buffer[data->i_buffer++] = *data->cp;
			data->cp++;
		}
	}
	if (cas == 1)
	{
		data->ot_buffer[data->i_buffer++] = *data->s;
		data->s++;
	}
}

int	construct_ot_string(t_c_data *data)
{
	while (*data->s)
	{
		if (*data->s == '%')
		{
			data->cp = data->s;
			data->s++;
			if (get_format(data) == ERROR_INCORECT_INPUT_FORMAT)
			{
				if (data->i_buffer > SIZE_BUFFER - 1)
					flush_ot_buffer(data);
				fill(data, 0);
			}
		}
		else
		{
			if (data->i_buffer > SIZE_BUFFER - 1)
				flush_ot_buffer(data);
			else
				fill(data, 1);
		}
	}
	return (OK);
}

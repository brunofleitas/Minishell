/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_buffers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:06:54 by pcasagra          #+#    #+#             */
/*   Updated: 2024/08/04 15:43:59 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*                                 FLUSH_BUFFER                               */
/* ************************************************************************** */
void	flush_ot_buffer(t_c_data *data)
{
	int	i;

	i = 0;
	while (i < data->i_buffer)
	{
		ft_putchar_fd(data->ot_buffer[i], 1);
		data->r_value += 1;
		data->ot_buffer[i] = 0;
		i++;
	}
	data->i_buffer = 0;
}

void	empty_format_substr(t_c_data *data)
{
	int	i;

	i = 0;
	while (data->format_substr[i] != '\0')
	{
		data->format_substr[i] = 0;
		i++;
	}
}

void	flush_format_substr_else(t_c_data *data, t_struc *ts)
{
	int	j;

	j = 0;
	if (data->i_buffer + ts->s > SIZE_BUFFER - 1)
		flush_ot_buffer(data);
	while (j < ts->s)
	{
		data->ot_buffer[data->i_buffer] = data->format_substr[j];
		data->i_buffer++;
		j++;
	}
	ts->s = 0;
	empty_format_substr(data);
}

void	flush_format_substr_s(t_c_data *data, t_st_s *ts)
{
	int	j;

	j = 0;
	if (data->i_buffer + ts->s > SIZE_BUFFER - 1)
		flush_ot_buffer(data);
	while (j < ts->s)
	{
		data->ot_buffer[data->i_buffer] = data->format_substr[j];
		data->i_buffer++;
		j++;
	}
	ts->s = 0;
	empty_format_substr(data);
}

void	flush_format_abs(t_c_data *data)
{
	int	i;

	i = 0;
	while (data->format_abs[i] != '\0')
	{
		data->format_abs[i] = 0;
		i++;
	}
}

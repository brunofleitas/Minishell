/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_mini_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:27:31 by pcasagra          #+#    #+#             */
/*   Updated: 2024/03/13 09:27:35 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	size_format_abs(t_c_data *data)
{
	int					size;
	unsigned long long	t_arg;
	long long			base;

	base = data->str_format.base;
	t_arg = get_output_type(data);
	size = 0;
	if (data->rva.a_s == 1)
	{
		data->format_abs[0] = '-';
		size++;
	}
	while ((t_arg / base) != 0)
	{
		t_arg /= base;
		size++;
	}
	size++;
	data->len_abs = size;
}

static char	*get_base(t_c_data *data)
{
	if (data->str_format.base == BASE_HEX_16
		&& data->str_format.specifier == 'X')
		return (UHEX);
	else if (data->str_format.base == BASE_HEX_16
		&& data->str_format.specifier != 'X')
		return (HEX);
	else
		return (DEC);
}

static void	exec_unsigned(t_c_data *data, int i, int stop, char *b)
{
	unsigned long long	t_arg;

	t_arg = get_output_type(data);
	while (i - stop)
	{
		data->format_abs[i] = b[t_arg % data->str_format.base];
		t_arg /= data->str_format.base;
		i--;
	}
	data->format_abs[i] = b[t_arg % data->str_format.base];
}

static void	exec_signed(t_c_data *data, int i, int stop, char *b)
{
	unsigned long long	t_arg;

	t_arg = get_output_type(data);
	while (i - stop)
	{
		data->format_abs[i] = b[t_arg % data->str_format.base];
		t_arg /= data->str_format.base;
		i--;
	}
	data->format_abs[i] = b[t_arg % data->str_format.base];
}

void	mini_itoa(t_c_data *data, int u)
{
	int		i;
	int		stop;
	char	*b;

	size_format_abs(data);
	i = data->len_abs - 1;
	stop = 0;
	if (data->rva.a_s == 1)
		stop = 1;
	b = get_base(data);
	if (u == 1)
		exec_unsigned(data, i, stop, b);
	if (u == -1)
		exec_signed(data, i, stop, b);
}

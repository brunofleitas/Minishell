/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   47-builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:47:55 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:38:31 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	convert_to_ll(const char *str, int *i, int sign, int *error)
{
	long long	result;
	int			digit;

	result = 0;
	while (str[*i] && isdigit(str[*i]))
	{
		digit = str[*i] - '0';
		if (result > (LLONG_MAX - digit) / 10)
		{
			*error = 1;
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = result * 10 + digit;
		(*i)++;
	}
	return (sign * result);
}

long long	ft_strtoll(const char *str, int *error)
{
	int			sign;
	int			i;
	long long	result;

	sign = 1;
	i = 0;
	result = 0;
	*error = 0;
	i = skip_whitespace(str, i);
	sign = get_sign(str, &i);
	result = convert_to_ll(str, &i, sign, error);
	if (i == 0 || (i == 1 && (str[0] == '-' || str[0] == '+')))
	{
		*error = 1;
		return (0);
	}
	return (result);
}

int	checkoverflow(char *str)
{
	int	digits;
	int	count;

	count = 0;
	if (*str == '-')
		count = 1;
	digits = ft_strlen(str + count);
	if (digits > 19)
		return (1);
	if (digits == 19)
	{
		if (count == 0)
		{
			if (!(ft_strncmp(str, "9223372036854775807", digits) <= 0))
				return (1);
		}
		else
		{
			if (!(ft_strncmp(str, "-9223372036854775808", 20) <= 0))
				return (1);
		}
	}
	return (0);
}

int	validate_exit_args(char **args)
{
	int			error;
	long long	exit_code;

	exit_code = ft_strtoll(args[1], &error);
	if (is_number_argument(args[1]) && !checkoverflow(args[1]))
		return ((int)(exit_code % 256));
	if (error)
	{
		ft_putstr_fd("minishell", 2);
		ft_putstr_fd(": exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (args[2] != NULL)
	{
		ft_putstr_fd("minishell", 2);
		ft_putstr_fd(": exit: too many arguments\n", 2);
		return (0);
	}
	return ((int)(exit_code % 256));
}

void	builtin_exit(t_ma *ma, char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args == NULL || args[1] == NULL)
		clean_exit(0, ma);
	else if ((args[1] != NULL) && (ft_strncmp(args[1], "0", 2) == 0))
		clean_exit(0, ma);
	else
	{
		exit_code = validate_exit_args(args);
		if (exit_code)
			clean_exit(exit_code, ma);
		else
			ma->last_exit_status = 1;
	}
}

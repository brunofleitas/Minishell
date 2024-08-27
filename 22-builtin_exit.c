/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22-builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:47:55 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/27 17:21:33 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int is_valid_argument(char *arg)
{ 
    int i;

	i = 1;
    if (arg[0] == '+' || arg[0] == '-')
	{
        while (arg[i] != '\0')
		{
            if (!isdigit(arg[i]))
                return 0;
            i++;
        }
        return 1;
    }
    return 0;
}

static void	clean_exit(int exit_code, t_ma *ma)
{
	free_memory(&(ma->first_node));
	free_memory(&(ma->first_env));
	clear_history();
	exit(exit_code);
}

long long ft_strtoll(const char *str, int *error)
{
    long long result = 0;
    int sign = 1;
    int i = 0;

    *error = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
        i++;
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] && isdigit(str[i])) {
        int digit = str[i] - '0';
        if (result > (LLONG_MAX - digit) / 10) {
            *error = 1;
            return (sign == 1 ? LLONG_MAX : LLONG_MIN);
        }
        result = result * 10 + digit;
        i++;
    }
    if (i == 0 || (i == 1 && (str[0] == '-' || str[0] == '+')))
	{
	    *error = 1;
        return 0;
	}
    return sign * result;
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

int is_number_argument(char *arg)
{
    int i = 1;

    if (arg[0] == '+' || arg[0] == '-')
	{
        while (arg[i] != '\0')
		{
            if (!isdigit(arg[i]))
                return 0; 
            i++;
        }
        return 1;
    }
    return 0;
}

static int validate_exit_args(char **args)
{
    int error;
    long long exit_code;

    if (args[2] != NULL) {
        ft_putstr_fd("minishell", 2);
        ft_putstr_fd(": exit: too many arguments\n", 2);
        return (1);
    }
	exit_code = ft_strtoll(args[1], &error);
	if (is_number_argument(args[1]) && !checkoverflow(args[1]))
		return((int)(exit_code % 256));
    if (error)
	{
        ft_putstr_fd("minishell", 2);
        ft_putstr_fd(": exit: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        return (2);
    }
    return ((int)(exit_code % 256));
}

void	builtin_exit(t_ma *ma, char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args == NULL || args[1] == NULL)
	{
		clean_exit(0, ma);
	}
	else
	{
		exit_code = validate_exit_args(args);
		if (exit_code)
		{
			clean_exit(exit_code, ma);
		}
	}
}

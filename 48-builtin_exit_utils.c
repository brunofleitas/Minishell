/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   48-builtin_exit_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 03:18:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:40:06 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_argument(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '+' || arg[0] == '-')
	{
		while (arg[i] != '\0')
		{
			if (!isdigit(arg[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	clean_exit(int exit_code, t_ma *ma)
{
	free_memory(&(ma->first_node));
	free_memory(&(ma->first_env));
	clear_history();
	exit(exit_code);
}

int	skip_whitespace(const char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	return (i);
}

int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	is_number_argument(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '+' || arg[0] == '-')
	{
		while (arg[i] != '\0')
		{
			if (!isdigit(arg[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22-builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:47:55 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/25 08:47:02 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

static void	clean_exit(int exit_code, t_ma *ma)
{
	free_memory(&(ma->first_node));
	free_memory(&(ma->first_env));
	clear_history();
	exit(exit_code);
}

static int	validate_exit_args(char **args)
{
	if (args[2] != NULL)
	{
		print_error("exit: too many arguments\n");
		return (1);
	}
	if (!ft_atoi(args[1]))
	{
		print_error("exit: numeric argument required\n");
		return (2);
	}
	return (ft_atoi(args[1]) % 256);
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
		if (exit_code != 1)
		{
			clean_exit(exit_code, ma);
		}
	}
}

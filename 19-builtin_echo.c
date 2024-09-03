/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19-builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:50:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/03 21:47:17 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

/**
 * Checks if the "-n" flag is present in the echo command arguments.
 *
 * @param args Array of command arguments.
 * @return 1 if "-n" flag is not present, 0 if it is present.
 */
static int	should_add_newline(char **args)
{
	int	i;

	i = 1;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	if (i == 1)
		return (1);
	return (0);
}

/**
 * Handles the $? special parameter in echo command.
 *
 * @param arg The argument to check.
 * @param ma Pointer to the main structure containing last exit status.
 * @return The value to be printed (either $? or the last exit status).
 */

/**
 * Prints the echo command arguments.
 *
 * @param args Array of command arguments.
 * @param start_index The index to start printing from.
 * @param ma Pointer to the main structure.
 */
static void	print_echo_args(char **args, int start_index)
{
	int		i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] && (!(ft_isdigit(args[i + 1][0]) && args[i + 1][1] == '\0'))
			&& (!(ft_isdigit(args[i][0]) && args[i][1] == '\0')))
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

/**
 * Executes the built-in echo command.
 *
 * This function mimics the behavior of the original bash echo command.
 * It handles the -n flag and the $? special parameter.
 *
 * @param args The array of arguments.
 * @param word_count The number of words in the array.
 * @param ma A pointer to the t_ma structure.
 * @return Always returns EXIT_SUCCESS (0).
 */
void	builtin_echo(char **args, int word_count, t_ma *ma)
{
	int	newline;
	int	start_index;

	(void)word_count;
	newline = should_add_newline(args);
	start_index = 1;
	while (args[start_index] && ft_strcmp(args[start_index], "-n") == 0)
		start_index++;
	print_echo_args(args, start_index);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exit_or_setexit(0,0, ma);
}

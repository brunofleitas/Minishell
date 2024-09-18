/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37-builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:50:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:28:28 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the "-n" flag is present in the echo command arguments.
 *
 * @param args Array of command arguments.
 * @return 1 if "-n" flag is not present, 0 if it is present.
 */
int	should_add_newline(char **args)
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
 * @brief Prints the arguments of the echo command starting from a given index.
 *
 * This function iterates through the provided arguments array starting from
 * the specified index and prints each argument to the standard output. If the
 * current argument is not the last one, a space is printed after it unless
 * both the current and next arguments are single-digit numbers.
 *
 * @param args The array of arguments to be printed.
 * @param start_index The index from which to start printing the arguments.
 */
void	print_echo_args(char **args, int start_index)
{
	int		i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1]
			&& (!(ft_isdigit(args[i + 1][0])
				&& args[i + 1][1] == '\0'))
				&& (!(ft_isdigit(args[i][0])
				&& args[i][1] == '\0')))
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

/**
 * @brief Executes the echo built-in command.
 *
 * This function handles the echo command, which prints its arguments to the
 * standard output. It supports the `-n` option to suppress the trailing newline.
 *
 * @param args The arguments passed to the echo command.
 * @param word_count The number of arguments passed to the echo command.
 * @param ma A pointer to the Minishell's main structure.
 *
 * The function determines whether to add a newline at the end of the output
 * based on the presence of the `-n` option. It then prints the arguments
 * starting from the first non-option argument. Finally, it either exits the
 * process or sets the exit status to 0.
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
	exit_or_setexit(0, 0, ma);
}

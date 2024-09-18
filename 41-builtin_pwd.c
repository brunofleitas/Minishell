/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20-builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:00 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/15 02:15:49 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the built-in 'pwd' command.
 *
 * This function prints the current working directory to the standard output.
 * If the 'PWD' environment variable is set, it prints its value. Otherwise,
 * it writes an error message to the standard error.
 *
 * @param args Unused parameter.
 * @param ma Pointer to the main structure containing environment variables.
 */
void	builtin_pwd(char **args, t_ma *ma)
{
	(void)args;
	if (get_env("PWD", (ma->env->var)) != NULL)
	{
		ft_printf("%s\n", get_env("PWD", (ma->env->var)));
		exit_or_setexit(0, 0, ma);
	}
	else
	{
		write(STDERR_FILENO, "getcwd() error\n", 14);
		exit_or_setexit(1, 0, ma);
	}
}

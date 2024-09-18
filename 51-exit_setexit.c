/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   51-exit_setexit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 03:52:28 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 03:47:15 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Exits the shell if the given error code is non-zero.
 *
 * @param e The error code to check. Set to 0 if no error occurred,
	non-zero an error occured.
 * @param e_throw_err If true, an error message is printed.

	* @param ma The main structure containing the necessary information for 
    the shell.
 */
void	exit_or_setexit(int e, int e_throw_err, t_ma *ma)
{
	(void)e_throw_err;
	if (!e)
	{
		if (ma->in_child_p && !ma->and_or)
		{
			exit(EXIT_SUCCESS);
		}
		else
			ma->last_exit_status = e;
	}
	else
	{
		if (e_throw_err)
			perror(" ");
		if (ma->in_child_p && !ma->and_or)
		{
			write(2, "\n", 1);
			exit(EXIT_FAILURE);
		}
		else
			ma->last_exit_status = e;
	}
}

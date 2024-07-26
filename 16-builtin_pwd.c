/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16-builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:00 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/26 02:57:08 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    first_node: Double pointer to the first t_ntc node.
  Return value:
    Pointer to a string containing the current working directory,
    or NULL if an error occurs.
  Description:
    Retrieves the current working directory using getcwd. If 
    successful, duplicates the directory string and returns it. 
    Prints an error message if getcwd fails.
*/
char	*builtin_pwd(t_ntc **first_node)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strdup_g_c(cwd, first_node));
	else
		ft_printf("getcwd() error");
	return (NULL);
}

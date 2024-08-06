/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14-builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:49:35 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/06 11:08:41 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int remove_env_var(t_env **env, char *name)
{
	int i;

	i = find_env_var(env, name);
	if (i == 0)
		return (1);
	while (i < (*env)->count - 1)
	{
		(*env)->var[i] = (*env)->var[i + 1];
		i++;
	}
	(*env)->var[(*env)->count - 1] = NULL;
	(*env)->count = (*env)->count - 1;
	return (0);
}

/*
  Parameters:
    env: Pointer to the environment variables.
    name: Name of the variable to unset.
  Return value:
    Returns 0.
  Description:
    Unsets (removes) an environment variable. Finds the variable 
    by name, frees its memory, shifts the subsequent variables in 
    the array, and decreases the environment variable count.
*/
int	builtin_unset(char **args, t_ma *ma)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (find_env_var(ma->env, args[i]) != 0)
			remove_env_var(ma->env, args[i]);
		i++;
	}
	return (0);
}

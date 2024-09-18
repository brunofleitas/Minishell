/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   45-builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:49:35 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:36:26 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds the index of an environment variable in the environment list.
 *
 * This function searches through the environment variables to find the one
 * that matches the given name. It compares the name with each environment
 * variable's name part (before the '=' character) and returns the index of
 * the matching variable.
 *
 * @param env A pointer to the environment list.
 * @param name The name of the environment variable to find.
 * @return The index of the environment variable if found, otherwise 0.
 */
int	find_env_var_u(t_env **env, char *name)
{
	int	i;

	i = 0;
	while (i < (*env)->count)
	{
		if (ft_strncmp(name, (*env)->var[i], ft_strlen(name)) == 0
			&& (*env)->var[i][ft_strlen(name)] == '=')
			return (i);
		i++;
	}
	return (0);
}

/**
 * remove_env_var - Removes an environment variable from the environment list.
 * @env: Double pointer to the environment list.
 * @name: Name of the environment variable to be removed.
 *
 * This function searches for the environment variable with the given name
 * in the environment list. If found, it removes the variable by shifting
 * the subsequent variables up in the list and decreases the count of
 * environment variables.
 *
 * Return: 0 on success, 1 if the variable is not found.
 */
int	remove_env_var(t_env **env, char *name)
{
	int	i;

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

/**
 * @brief Checks if a given string contains an equal sign ('=').
 *
 * This function iterates through the provided string to determine if it
 * contains an equal sign. If an equal sign is found, an error message is
 * printed to the standard error output indicating that the parameter name
 * is invalid.
 *
 * @param str The string to be checked for an equal sign.
 * @return Returns 1 if an equal sign is found, otherwise returns 0.
 */
int	check_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": invalid parameter name\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * builtin_unset - Unsets environment variables specified in args.
 * @args: Array of strings, each an environment variable name to unset.
 * @ma: Pointer to a structure containing the environment variables.
 *
 * This function iterates through the provided arguments and unsets the 
 * corresponding environment variables from the environment list in ma.
 * It skips arguments containing an equal sign ('=') and continues to the 
 * next argument. If an environment variable is found, it is removed from 
 * the environment list. Finally, it calls exit_or_setexit to handle the 
 * exit status.
 */
void	builtin_unset(char **args, t_ma *ma)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!check_for_equal(args[i]))
		{
			while (args[i])
			{
				if (find_env_var_u(&ma->env, args[i]))
					remove_env_var(&ma->env, args[i]);
				i++;
			}
			break ;
		}
		if (find_env_var_u(&ma->env, args[i]) != 0)
			remove_env_var(&ma->env, args[i]);
		i++;
	}
	exit_or_setexit(0, 0, ma);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42-builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:59:49 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/24 00:51:16 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the addition or update of an environment variable.
 *
 * This function checks if the specified variable already exists in the 
 * environment. If it does, it attempts to update its value. If the variable 
 * does not exist, it tries to add it to the environment. The function 
 * manages the exit status appropriately based on the success of these 
 * operations.
 *
 * @param var The environment variable to add or update.
 * @param ma Pointer to the structure containing environment variables and 
 *           memory management.
 * @return 0 on success, 1 on failure (with an exit).
 */
int	handle_var(char *var, t_ma *ma)
{
	int	i;

	i = find_env_var(&(ma->env), var);
	if (i >= 0)
	{
		if (!update_env_var(i, var, ma))
		{
			exit_or_setexit(0, 0, ma);
			return (1);
		}
	}
	else
	{
		if (!add_env_var(var, ma))
		{
			printf("test add_env_var\n");
			exit_or_setexit(0, 0, ma);
			return (1);
		}
	}
	return (0);
}

/**
 * @brief Executes the built-in `export` command to set environment variables.
 *
 * This function handles the export of environment variables. If no arguments 
 * are provided, it prints the current environment. For each variable to be 
 * exported, it checks if the variable name is valid. If valid, it calls 
 * `handle_var` to process it. If any variable is invalid, an error message 
 * is printed. The function exits with the appropriate status.
 *
 * @param words_arr Array of strings representing the command and its arguments.
 * @param ma Pointer to the structure containing environment and memory 
 * 			 management.
 */
void	builtin_export(char **words_arr, t_ma *ma)
{
	char	**words_cpy;

	if (!words_arr[1])
	{
		print_env(ma->env);
		exit_or_setexit(0, 0, ma);
		return ;
	}
	words_cpy = words_arr + 1;
	while (*words_cpy)
	{
		if (!is_valid_var(*words_cpy))
		{
			write(2, "minishell: export: `", 20);
			write(2, *words_cpy, ft_strlen(*words_cpy));
			write(2, "': not a valid identifier\n", 26);
		}
		else
		{
			if (handle_var(*words_cpy, ma))
				return ;
		}
		words_cpy++;
	}
	exit_or_setexit(0, 0, ma);
}

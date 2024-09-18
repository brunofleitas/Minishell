/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   46-builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:37:28 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Calculates the total length of all environment variables.
 *
 * This function iterates through the environment variables stored in the 
 * t_env structure and sums up the lengths of each variable, including an 
 * additional byte for each variable to account for the null terminator.
 *
 * @param env A pointer to the t_env structure containing the environment 
 * variables.
 * @return The total length of all environment variables, including null 
 * terminators.
 */
size_t	calculate_total_env_length(t_env *env)
{
	size_t	total_length;
	int		i;

	total_length = 0;
	i = 0;
	while (env->var[i] != NULL)
	{
		total_length += ft_strlen(env->var[i]) + 1;
		i++;
	}
	return (total_length);
}

/**
 * concatenate_env_vars - Concatenates environment variables into a single 
 * string.
 * 
 * @env: Pointer to the environment variables structure.
 * @total_length: The total length of the concatenated string.
 * @ma: Pointer to the memory allocator structure.
 * 
 * This function allocates memory for a new string that will contain all the
 * environment variables concatenated together, each followed by a newline 
 * character. If memory allocation fails, the function will either exit or 
 * set an exit status.
 * 
 * Return: A pointer to the concatenated string.
 */
char	*concatenate_env_vars(t_env *env, size_t total_length, t_ma *ma)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)ft_calloc_g_c((total_length + 1), sizeof(char),
			&(ma->first_node));
	if (!result)
		exit_or_setexit(1, 1, ma);
	while (env->var[i] != NULL)
	{
		ft_strlcat(result, env->var[i], total_length + 1);
		ft_strlcat(result, "\n", total_length + 1);
		i++;
	}
	return (result);
}

/**
 * @brief Executes the 'env' builtin command which prints the environment 
 * variables.
 *
 * This function handles the 'env' command in the Minishell. It checks if there 
 * are any arguments passed to the command. If there are, it prints an error 
 * message and exits with a status code of 1. If no arguments are passed, it 
 * calculates the total length of the environment variables, concatenates them 
 * into a single string, and prints the result. If the concatenation is 
 * successful, it exits with a status code of 0. Otherwise, it exits with a 
 * status code of 1.
 *
 * @param args The arguments passed to the 'env' command.
 * @param ma A pointer to the main structure containing the environment 
 * variables.
 */
void	builtin_env(char **args, t_ma *ma)
{
	size_t	total_length;
	char	*result;

	if (args[1] != NULL)
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, "env: too many arguments\n", 24);
		exit_or_setexit(1, 0, ma);
	}
	total_length = calculate_total_env_length(ma->env);
	result = concatenate_env_vars(ma->env, total_length, ma);
	if (result)
	{
		printf("%s", result);
		exit_or_setexit(0, 0, ma);
	}
	exit_or_setexit(1, 1, ma);
}

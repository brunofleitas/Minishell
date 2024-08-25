/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-build_env_structure.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:53:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 17:54:53 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of environment variables.
 *
 * This function iterates through the provided array of environment
 * variables and counts the number of variables present.
 *
 * @param envp Array of environment variables.
 * @return int The count of environment variables.
 */
static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

/**
 * @brief Allocates memory for the environment variables.
 *
 * This function allocates memory for a new array of environment
 * variables, including space for a NULL terminator. If the allocation
 * fails, it writes an error message to standard error.
 *
 * @param first_node Pointer to the first node in the garbage collector
 *                   linked list.
 * @param count The number of environment variables.
 * @return char** Pointer to the newly allocated array of environment
 *                variables, or NULL if allocation fails.
 */
static char	**allocate_env(t_ntc **first_node, int count)
{
	char	**new_envp;

	new_envp = (char **)g_c(first_node, (count + 1) * sizeof(char *))->data;
	if (!new_envp)
	{
		write(2, "malloc error\n", 13);
		return (NULL);
	}
	return (new_envp);
}

/**
 * @brief Duplicates the environment variables.
 *
 * This function creates a new t_env structure and duplicates the
 * provided environment variables into it. It uses the garbage
 * collector to manage memory allocation. If any allocation fails, it
 * writes an error message to standard error and exits the program.
 *
 * @param first_node Pointer to the first node in the garbage collector
 *                   linked list.
 * @param envp Array of environment variables to duplicate.
 * @return t_env* Pointer to the newly created t_env structure.
 */
t_env	*duplicate_vars(t_ntc **first_node, char **envp)
{
	t_env	*env;
	int		i;

	env = g_c(first_node, sizeof(t_env))->data;
	env->count = count_env_vars(envp);
	env->var = allocate_env(first_node, env->count);
	if (!env->var)
		return (env);
	i = 0;
	while (i < env->count)
	{
		env->var[i] = ft_strdup_g_c(envp[i], first_node);
		if (!env->var[i])
		{
			write(2, "ft_strdup_g_c error\n", 20);
			free_memory(first_node);
			exit(1);
		}
		i++;
	}
	env->var[env->count] = NULL;
	return (env);
}

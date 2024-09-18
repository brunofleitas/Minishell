/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-build_env_structure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:53:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 05:26:24 by bfleitas         ###   ########.fr       */
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
int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

/**
 * @brief Allocates memory for a new environment array.
 *
 * This function allocates memory for a new environment array based on the 
 * provided count. It uses a custom memory allocation function `g_c` to 
 * allocate the required memory and returns a pointer to the newly allocated 
 * environment array. If the allocation fails, an error message is written to 
 * the standard error output and the function returns NULL.
 *
 * @param first_node A pointer to the first node of a custom data structure 
 *                   used by the `g_c` function for memory allocation.
 * @param count The number of environment variables to allocate space for.
 * @return A pointer to the newly allocated environment array, or NULL if 
 *         the allocation fails.
 */
char	**allocate_env(t_ntc **first_node, int count)
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

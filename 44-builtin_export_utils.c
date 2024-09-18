/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   44-builtin_export_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 03:00:49 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 03:12:35 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Swaps two pointers to strings.
 *
 * This function swaps the values of two string pointers. It uses a temporary 
 * pointer to facilitate the swap without losing the original values.
 *
 * @param a Pointer to the first string pointer.
 * @param b Pointer to the second string pointer.
 */
void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Creates a copy of the environment variable array.
 *
 * This function allocates memory for a new array of strings and copies 
 * the environment variables from the provided environment structure into 
 * the new array. If memory allocation fails, it returns NULL.
 *
 * @param env Pointer to the environment structure containing variables.
 * @return A newly allocated array of environment variable strings, or NULL 
 *         if allocation fails.
 */
char	**copy_env(t_env *env)
{
	char	**sorted_env;
	int		i;

	sorted_env = (char **)malloc(sizeof(char *) * env->count);
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (i < env->count)
	{
		sorted_env[i] = env->var[i];
		i++;
	}
	return (sorted_env);
}

/**
 * @brief Finds the index of an environment variable by name.
 *
 * This function searches for an environment variable in the provided 
 * environment structure. It compares each variable's name up to the 
 * equals sign (`=`) with the given name. If found, it returns the index; 
 * otherwise, it returns -1.
 *
 * @param env Pointer to the environment structure containing variables.
 * @param var The environment variable name to search for.
 * @return The index of the variable if found, or -1 if not found.
 */
int	find_env_var(t_env **env, char *var)
{
	int	len;
	int	i;

	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	i = 0;
	while (i < (*env)->count)
	{
		if (ft_strncmp((*env)->var[i], var, len) == 0
			&& (*env)->var[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Updates an existing environment variable with a new value.
 *
 * This function updates the environment variable at the specified index 
 * with the new value. It duplicates the provided variable string using 
 * `ft_strdup_g_c`. If the duplication fails, an error message is printed, 
 * and the function returns an error code.
 *
 * @param i The index of the environment variable to update.
 * @param var The new value for the environment variable.
 * @param ma Pointer to the structure containing environment variables and 
 *           memory management.
 * @return 0 on success, 1 on failure.
 */
int	update_env_var(int i, const char *var, t_ma *ma)
{
	ma->env->var[i] = ft_strdup_g_c(var, &(ma->first_env));
	if (!(ma->env->var[i]))
	{
		write(2, "ft_strdup_g_c error\n", 20);
		return (1);
	}
	return (0);
}

/**
 * @brief Checks if a given string is a valid environment variable name.
 *
 * This function verifies that the first character of the variable name 
 * is an alphabetic character or an underscore. It then checks the remaining 
 * characters to ensure they are alphanumeric or underscores. The function 
 * returns 1 if the variable name is valid, and 0 otherwise.
 *
 * @param var The string to check for validity as an environment variable name.
 * @return 1 if valid, 0 if invalid.
 */
int	is_valid_var(char *var)
{
	if (!ft_isalpha(*var) && *var != '_')
		return (0);
	var++;
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
			return (0);
		var++;
	}
	return (1);
}

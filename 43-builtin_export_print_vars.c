/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   43-builtin_export_print_vars.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:56:05 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 05:11:21 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a new environment variable to the environment array.
 *
 * This function reallocates memory for the environment variable array and 
 * adds a new variable to it. If memory allocation fails or if duplicating 
 * the variable string fails, an error message is printed, and the function 
 * returns 0. The function also updates the count of environment variables.
 *
 * @param var The environment variable string to add.
 * @param ma Pointer to the structure containing environment variables and 
 *           memory management.
 * @return 1 on success, 0 on failure.
 */
int	add_env_var(char *var, t_ma *ma)
{
	char	**new_var;

	new_var = ft_realloc_g_c(&(ma->first_env), ma->env->var, (ma->env->count
				+ 2) * sizeof(char *));
	if (!new_var)
	{
		perror("realloc");
		return (0);
	}
	ma->env->var = new_var;
	ma->env->var[ma->env->count] = ft_strdup_g_c(var, &(ma->first_env));
	if (!(*ma->env->var[ma->env->count]))
	{
		write(2, "ft_strdup_g_c error\n", 20);
		return (0);
	}
	ma->env->count++;
	ma->env->var[ma->env->count] = NULL;
	return (1);
}

/**
 * @brief Prints the value of an environment variable, escaping quotes.
 *
 * This function prints the value of an environment variable, surrounded 
 * by double quotes. If the value contains a double quote, it escapes it 
 * with a backslash. Each character is written to standard output.
 *
 * @param env_value The value of the environment variable to print.
 */
void	print_env_value(const char *env_value)
{
	int	k;

	k = 0;
	write(1, "=\"", 2);
	while (env_value[k])
	{
		if (env_value[k] == '"')
			write(1, "\\", 1);
		write(1, &env_value[k], 1);
		k++;
	}
	write(1, "\"", 1);
}

/**
 * @brief Prints the sorted environment variables to standard output.
 *
 * This function iterates over an array of sorted environment variables 
 * and prints each variable in the format `declare -x VARIABLE=value`. 
 * If a variable has a value, it calls `print_env_value` to print it. 
 * Each variable is printed on a new line.
 *
 * @param sorted_env Array of sorted environment variable strings.
 * @param count The number of environment variables to print.
 */
void	print_sorted_env(char **sorted_env, int count)
{
	int	i;
	int	len;

	i = 0;
	while (i < count)
	{
		len = 0;
		write(1, "declare -x ", 11);
		while (sorted_env[i][len] && sorted_env[i][len] != '=')
			len++;
		write(1, sorted_env[i], len);
		if (sorted_env[i][len] == '=')
			print_env_value(&sorted_env[i][len + 1]);
		write(1, "\n", 1);
		i++;
	}
}

/**
 * @brief Sorts an array of environment variables in lexicographical order.
 *
 * This function implements a bubble sort algorithm to sort the given 
 * array of environment variables. It compares adjacent strings and swaps 
 * them if they are out of order. The sorting continues until no swaps 
 * are made in a pass, indicating that the array is sorted.
 *
 * @param sorted_env Array of environment variable strings to be sorted.
 * @param count The number of environment variables in the array.
 */
void	sort_env(char **sorted_env, int count)
{
	int		i;
	int		j;
	int		sorted;

	i = 0;
	while (i < count - 1)
	{
		sorted = 0;
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
			{
				swap(&sorted_env[j], &sorted_env[j + 1]);
				sorted = 1;
			}
			j++;
		}
		if (!sorted)
			break ;
		i++;
	}
}

/**
 * @brief Prints the environment variables in sorted order.
 *
 * This function creates a copy of the environment variables, sorts them, 
 * and then prints the sorted list to the standard output. If the copy 
 * fails, the function returns without performing any action.
 *
 * @param env Pointer to the environment structure containing variables.
 */
void	print_env(t_env *env)
{
	char	**sorted_env;

	sorted_env = copy_env(env);
	if (!sorted_env)
		return ;
	sort_env(sorted_env, env->count);
	print_sorted_env(sorted_env, env->count);
	free(sorted_env);
}

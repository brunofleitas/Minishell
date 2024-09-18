/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39-builtin_cd_env_vars.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:37:58 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 05:20:30 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrieves the index and value of an environment variable.
 *
 * This function searches for an environment variable by name in the 
 * environment structure. If found, it returns the index of the variable 
 * and sets the provided value pointer to point to its value. If the 
 * variable is found but has an empty value, it returns -1. If the variable 
 * is not found, it sets the value to NULL and also returns -1.
 *
 * @param env Pointer to the environment structure containing variables.
 * @param name The name of the environment variable to search for.
 * @param value Pointer to a string pointer where the variable's value 
 *              will be stored if found.
 * @return The index of the variable if found, or -1 if not found or if 
 *         the value is empty.
 */
int	get_env_var(t_env **env, const char *name, char **value)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while ((*env)->var[i])
	{
		if (ft_strncmp((*env)->var[i], name, name_len) == 0
			&& (*env)->var[i][name_len] == '=')
		{
			*value = (*env)->var[i] + name_len + 1;
			if (value[0][0] == '\0')
				return (-1);
			return (i);
		}
		i++;
	}
	*value = NULL;
	return (-1);
}

/**
 * @brief Adds a new environment variable to the environment array.
 *
 * This function reallocates memory for the environment variable array and 
 * adds a new variable to it. If memory allocation fails or if duplicating 
 * the variable string fails, an error message is printed, and the function 
 * returns an error code. The function also updates the count of environment 
 * variables.
 *
 * @param var The environment variable string to add.
 * @param ma Pointer to the structure containing environment variables and 
 *           memory management.
 * @return 0 on success, 1 on failure.
 */
int	add_env_var_cd(char *var, t_ma *ma)
{
	char	**new_var;

	new_var = ft_realloc_g_c(&(ma->first_env), ma->env->var, (ma->env->count
				+ 2) * sizeof(char *));
	if (!new_var)
	{
		perror("realloc");
		return (1);
	}
	ma->env->var = new_var;
	ma->env->var[ma->env->count] = ft_strdup_g_c(var, &(ma->first_env));
	if (!(*ma->env->var[ma->env->count]))
	{
		write(2, "ft_strdup_g_c error\n", 20);
		return (1);
	}
	ma->env->count++;
	ma->env->var[ma->env->count] = NULL;
	return (0);
}

/**
 * @brief Updates the OLDPWD environment variable with the current directory.
 *
 * This function sets the OLDPWD variable to the current directory. If the 
 * OLDPWD variable does not exist, it creates it. If it exists, it updates 
 * its value. If the update fails, an error message is printed, and the 
 * function returns an error code.
 *
 * @param current_dir The current directory to set as the OLDPWD value.
 * @param ma Pointer to the structure containing environment variables and 
 *           memory management.
 * @return 0 on success, 1 on failure.
 */
int	update_oldpwd(char *current_dir, t_ma *ma)
{
	char	*oldpwd_str;
	char	*temp;
	int		i;

	i = get_env_var(&ma->env, "OLDPWD", &temp);
	if (i == -1)
	{
		add_env_var_cd(ft_strjoin_g_c("OLDPWD=", current_dir, &ma-> \
			first_env), ma);
	}
	if (i != -1)
	{
		oldpwd_str = ft_strdup_g_c("", &ma->first_env);
		temp = ft_strjoin_g_c(oldpwd_str, "OLDPWD=", &ma->first_env);
		oldpwd_str = temp;
		temp = ft_strjoin_g_c(oldpwd_str, current_dir, &ma->first_env);
		oldpwd_str = temp;
		if (update_env_var(i, oldpwd_str, ma))
		{
			fprintf(stderr,
				"cd: failed to update OLDPWD environment variable\n");
			return (1);
		}
	}
	return (0);
}

/**
 * @brief Updates the value of the PWD environment variable.
 *
 * This function constructs a new PWD variable string using the provided 
 * current directory and updates the existing PWD environment variable. 
 * If the update fails, an error message is printed, and the function 
 * returns an error code.
 *
 * @param i The index of the existing PWD variable in the environment.
 * @param new_current_dir The new directory to set as the PWD value.
 * @param ma Pointer to the structure containing environment variables and 
 *           memory management.
 * @return 0 on success, 1 on failure.
 */
int	update_pwd_value(int i, char *new_current_dir, t_ma *ma)
{
	char	*pwd_str;
	char	*temp;

	pwd_str = ft_strdup_g_c("", &ma->first_env);
	temp = ft_strjoin_g_c(pwd_str, "PWD=", &ma->first_env);
	pwd_str = temp;
	temp = ft_strjoin_g_c(pwd_str, new_current_dir, &ma->first_env);
	pwd_str = temp;
	if (update_env_var(i, pwd_str, ma))
	{
		fprintf(stderr, "cd: failed to update PWD environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Updates the PWD environment variable with the current directory.
 *
 * This function retrieves the current working directory and updates the 
 * PWD environment variable. If the variable does not exist, it creates it 
 * with the current directory value. If the operation fails at any point, 
 * it returns an error code.
 *
 * @param ma Pointer to the structure containing environment variables and 
 *           memory management.
 * @return 0 on success, 1 on failure.
 */
int	update_pwd(t_ma *ma)
{
	char	new_current_dir[PATH_MAX];
	char	*temp;
	int		i;

	if (getcwd(new_current_dir, sizeof(new_current_dir)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	i = get_env_var(&ma->env, "PWD", &temp);
	if (i == -1)
	{
		add_env_var_cd(ft_strjoin_g_c("PWD=", new_current_dir, &ma->first_env),
			ma);
	}
	else
	{
		if (update_pwd_value(i, new_current_dir, ma))
			return (1);
	}
	return (0);
}

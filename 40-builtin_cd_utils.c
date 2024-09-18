/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40-builtin_cd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 07:58:18 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 05:17:54 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * check_valid_path - Checks if the given path is a valid directory.
 * @path: The path to check.
 *
 * This function uses the stat system call to check if the given path exists
 * and is a directory. If the path does not exist, it writes an error message
 * to the standard error. If the path exists but is not a directory, it also
 * writes an error message to the standard error.
 *
 * Return: 1 if the path is a valid directory, 0 otherwise.
 */
int	check_valid_path(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
	{
		write (2, "minishell: cd: ", 15);
		write (2, path, ft_strlen(path));
		write (2, ": No such file or directory\n", 28);
		return (0);
	}
	if (!S_ISDIR(sb.st_mode))
	{
		fprintf(stderr, "cd: not a directory: %s\n", path);
		return (0);
	}
	return (1);
}

/**
 * get_home_directory - Retrieves the home directory path from the env vars.
 * @env: A pointer to the environment variables list.
 *
 * This function searches the environment variables for the "HOME" variable
 * and returns its value. If the "HOME" variable is not found, it returns NULL.
 *
 * Return: A pointer to the home directory path, or NULL if not found.
 */
char	*get_home_directory(t_env **env)
{
	char	*home;

	home = NULL;
	get_env_var(env, "HOME", &home);
	return (home);
}

/**
 * validate_cd_path - Validates the given path for the 'cd' command.
 * @path: The path to be validated.
 *
 * This function checks if the provided path is valid for changing the
 * directory. It uses the check_valid_path function to determine the validity
 * of the path. If the path is valid, it returns 1; otherwise, it returns 0.
 *
 * Return: 1 if the path is valid, 0 otherwise.
 */
int	validate_cd_path(char *path)
{
	if (check_valid_path(path) == 0)
		return (0);
	return (1);
}

/**
 * change_directory - Changes the current working directory to the specified path
 * @path: The path to change the current working directory to.
 *
 * This function attempts to change the current working directory to the path
 * specified by the `path` parameter. If the change is successful, the function
 * returns 0. If the change fails, an error message is printed to standard error
 * and the function returns 1.
 *
 * Return: 0 on success, 1 on failure.
 */
int	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

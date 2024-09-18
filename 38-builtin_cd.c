/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   38-builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:45:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 02:55:39 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrieves the current working directory.
 *
 * This function fetches the current working directory and stores it in the 
 * provided buffer. If the operation fails, it prints an error message 
 * using `perror` and returns an error code.
 *
 * @param current_dir Buffer to store the current working directory path.
 * @return 0 on success, 1 on failure.
 */
int	get_current_directory(char *current_dir)
{
	if (getcwd(current_dir, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}

/**
 * @brief Retrieves the target path for the `cd` command.
 *
 * This function determines the target path for the `cd` command based on 
 * the provided arguments. If no argument is provided or if the argument 
 * is `"~"`, it returns the user's home directory. If a valid path is 
 * specified, it returns that path. If the path is invalid, it prints an 
 * error message and returns NULL.
 *
 * @param args Array of arguments for the `cd` command.
 * @param env Pointer to the environment variable structure.
 * @return The target path for the `cd` command, or NULL if an error occurs.
 */
char	*get_cd_path(char **args, t_env **env)
{
	char	*path;

	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		path = get_home_directory(env);
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (args[2] == NULL)
		path = args[1];
	else
	{
		fprintf(stderr, "cd: string not in pwd: %s\n", args[1]);
		return (NULL);
	}
	return (path);
}

/**
 * @brief Handles arguments for the `cd` command, checking for validity.
 *
 * This function checks the arguments passed to the `cd` command. If there 
 * are too many arguments (more than 2), it prints an error message and sets 
 * the exit status. It also handles the case where an empty string is passed 
 * as an argument. If an error is found, the function returns 1.
 *
 * @param args Array of arguments for the `cd` command.
 * @param ma Pointer to the structure containing environment and memory 
 *           management.
 * @return 1 if an error occurs or arguments are invalid, 0 otherwise.
 */
int	handle_cd_args(char **args, t_ma *ma)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		write(STDERR_FILENO, "minishell: cd: ", 15);
		write(STDERR_FILENO, "too many arguments\n", 19);
		exit_or_setexit(1, 0, ma);
		return (1);
	}
	if (args[1] && strcmp(args[1], "") == 0)
		return (1);
	return (0);
}

/**
 * @brief Updates the environment variables related to the current directory.
 *
 * This function updates the OLDPWD and PWD environment variables. It first
 * updates the OLDPWD variable with the current directory, and if successful,
 * it then updates the PWD variable.
 *
 * @param current_dir The current directory path.
 * @param ma A pointer to the t_ma structure containing environment information.
 * 
 * @return Returns 1 if any update fails, otherwise returns 0.
 */
int	update_env_variables(char *current_dir, t_ma *ma)
{
	if (update_oldpwd(current_dir, ma))
		return (1);
	if (update_pwd(ma))
		return (1);
	return (0);
}

/**
 * @brief Executes the built-in `cd` (change directory) command.
 *
 * This function changes the current working directory to the specified path. 
 * It first handles any arguments passed to the `cd` command, validates the 
 * target path, and then updates the environment variables accordingly. If 
 * any step fails, the function sets the exit status and returns.
 *
 * @param args Array of arguments for the `cd` command.
 * @param ma Pointer to the structure containing environment and memory
 * 			 management.
 */
void	builtin_cd(char **args, t_ma *ma)
{
	char	current_dir[PATH_MAX];
	char	*path;

	if (handle_cd_args(args, ma))
		return ;
	path = get_cd_path(args, &ma->env);
	if (!path || !validate_cd_path(path))
		return (exit_or_setexit(1, 0, ma));
	if (get_current_directory(current_dir))
		return (exit_or_setexit(1, 0, ma));
	if (change_directory(path))
		return (exit_or_setexit(1, 0, ma));
	if (update_env_variables(current_dir, ma))
		return (exit_or_setexit(1, 0, ma));
	exit_or_setexit(0, 0, ma);
}

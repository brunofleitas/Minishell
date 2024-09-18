/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   50-AST_execute_ext_cmd_errors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 03:26:33 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:42:27 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_permission_denied(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Permission denied\n", 20);
	exit(126);
}

void	print_error(const char *msg, const char *arg)
{
	write(2, "minishell: ", 11);
	write(2, arg, ft_strlen(arg));
	write(2, msg, ft_strlen(msg));
}

void	handle_dot_and_double_dot(char **words_arr)
{
	if (ft_strcmp(words_arr[0], ".") == 0)
	{
		print_error(": filename argument required\n", words_arr[0]);
		write(2, "minishell: usage: . filename [arguments]\n", 40);
		exit(127);
	}
	else if (ft_strcmp(words_arr[0], "..") == 0)
	{
		print_error(": command not found\n", words_arr[0]);
		exit(127);
	}
}

void	check_access_and_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		print_error(": Is a directory\n", path);
		exit(126);
	}
	if (access(path, F_OK) != 0)
	{
		print_error(": No such file or directory\n", path);
		exit(127);
	}
	else if (access(path, X_OK) != 0)
	{
		print_error(": Permission denied\n", path);
		exit(126);
	}
}

void	check_command_errors(char *command_path, char **words_arr)
{
	struct stat	path_stat;

	if (stat(command_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)
		&& ft_strcmp(words_arr[0], "./") == 0)
	{
		print_error(": Is a directory\n", command_path);
		exit(126);
	}
	else if (stat(words_arr[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		print_error(": command not found\n", words_arr[0]);
		exit(127);
	}
	else if (access(words_arr[0], F_OK) == 0)
	{
		if (access(words_arr[0], X_OK) != 0)
		{
			print_error(": Permission denied\n", words_arr[0]);
			exit(126);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16-builtin_cd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 07:58:18 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/27 19:33:37 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_path(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
	{
		perror("cd");
		return (0);
	}
	if (!S_ISDIR(sb.st_mode))
	{
		fprintf(stderr, "cd: not a directory: %s\n", path);
		//perror("cd");
		return (0);
	}
	return (1);
}

char	*get_home_directory(t_env **env)
{
	char	*home;

	home = NULL;
	get_env_var(env, "HOME", &home);
	return (home);
}

int	validate_cd_path(char *path)
{
	if (check_valid_path(path) == 0)
		return (0);
	return (1);
}

int	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	update_env_variables(char *current_dir, t_ma *ma)
{
	if (update_oldpwd(current_dir, ma))
		return (1);
	if (update_pwd(ma))
		return (1);
	return (0);
}

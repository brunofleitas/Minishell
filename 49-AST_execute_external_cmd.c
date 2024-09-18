/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   49-AST_execute_external_cmd.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 03:25:10 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 05:17:01 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(const char *path, const char *cmd, t_ntc **first_node)
{
	char	*full_path;
	int		len;
	int		len_path;
	int		len_cmd;

	len_path = ft_strlen(path);
	len_cmd = ft_strlen(cmd);
	len = len_path + len_cmd + 2;
	full_path = g_c(first_node, sizeof(char) * len)->data;
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

char	*check_path_access(char *cmd_path, char *cmd)
{
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
			handle_permission_denied(cmd);
	}
	return (NULL);
}

char	*search_in_paths(char **paths, char *cmd, t_ntc **first_node)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = join_path(paths[i], cmd, first_node);
		cmd_path = check_path_access(cmd_path, cmd);
		if (cmd_path)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_env **env, int *p_ue,
		t_ntc **first_node)
{
	char	**paths;
	char	*path_env;

	if (get_env_var(env, "PATH", &path_env) == -1)
	{
		*p_ue = 1;
		return (NULL);
	}
	paths = ft_split(path_env, ':', first_node);
	return (search_in_paths(paths, cmd, first_node));
}

void	execute_external_cmd(char **words_arr, t_env **env, t_ntc **first_node)
{
	char	*command_path;
	int		p_ue;

	p_ue = 0;
	command_path = NULL;
	if (!words_arr || !words_arr[0] || words_arr[0][0] == '\0')
		exit(0);
	if ((ft_strcmp(words_arr[0], ".") == 0) || (ft_strcmp(words_arr[0],
				"..") == 0))
		handle_dot_and_double_dot(words_arr);
	else if (words_arr[0][0] == '/' || (words_arr[0][0] == '.'
			&& words_arr[0][1] != '\0') || words_arr[0][0] == '~')
		command_path = ft_strdup_g_c(words_arr[0], first_node);
	else
		command_path = find_command_path(words_arr[0], env, &p_ue, first_node);
	check_command_errors(command_path, words_arr);
	if (p_ue)
		check_access_and_directory(words_arr[0]);
	if (!command_path)
	{
		print_error(": command not found\n", words_arr[0]);
		exit(127);
	}
	check_access_and_directory(command_path);
	exit(execve(command_path, words_arr, (*env)->var));
}

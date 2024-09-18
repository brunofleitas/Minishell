/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33-handle_inputs_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:56:47 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:23:28 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Generates a unique temporary file name for heredoc redirection.
 *
 * This function creates a unique temporary file name using a base path 
 * (e.g., `/tmp/heredoc_`) and a counter that increments with each call. 
 * The temporary file name is dynamically allocated and returned.
 *
 * @param ma Pointer to the structure containing metadata, including the 
 *           counter for generating unique file names.
 * @return A dynamically allocated string containing the temporary file name, 
 *         or NULL if memory allocation fails.
 */
char	*give_tmp_name(t_ma *ma)
{
	char		*temp_file_name;
	const char	*base;
	char		*counter_str;

	base = "/tmp/heredoc_";
	counter_str = ft_itoa_g_c(ma->tmp_file_counter++, &(ma->first_node));
	if (!counter_str)
	{
		return (NULL);
	}
	temp_file_name = ft_strjoin_g_c(base, counter_str, &(ma->first_node));
	if (!temp_file_name)
	{
		return (NULL);
	}
	return (temp_file_name);
}

/**
 * @brief Handles the expansion of environment variables in a heredoc line.
 *
 * This function checks if the current position in the heredoc line contains 
 * an environment variable (denoted by `$` followed by an alphanumeric character 
 * or underscore). If found, it retrieves the value of the environment variable 
 * and writes it to the specified file descriptor, then advances the line index.
 *
 * @param fd The file descriptor of the temporary file to write to.
 * @param line The input line being processed.
 * @param i Pointer to the current index in the line.
 * @param ma Pointer to the structure containing environment variables and 
 * 			 memory management.
 * @return 1 if the environment variable was handled, 0 otherwise.
 */
int	handle_env_variable(int fd, char *line, int *i, t_ma *ma)
{
	int		var_len;
	char	*temp;
	char	*env_value;

	if (line[*i] == '$' && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'))
	{
		var_len = 0;
		while (line[*i + var_len + 1] && (ft_isalnum(line[*i + var_len + 1])
				|| line[*i + var_len + 1] == '_'))
			var_len++;
		temp = ft_substr_g_c(line + *i + 1, 0, var_len, &(ma->first_node));
		env_value = get_env(temp, ma->env->var);
		if (env_value)
			write(fd, env_value, ft_strlen(env_value));
		*i += var_len + 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Handles the expansion of the exit status (`$?`) in a heredoc line.
 *
 * This function checks if the current position in the heredoc line contains 
 * the special sequence `$?`, which represents the last exit status. If found, 
 * it writes the exit status to the specified file descriptor and advances 
 * the line index.
 *
 * @param fd The file descriptor of the temporary file to write to.
 * @param line The input line being processed.
 * @param i Pointer to the current index in the line.
 * @param ma Pointer to the structure containing metadata, including the last 
 * 			 exit status.
 * @return 1 if the exit status was handled, 0 otherwise.
 */
int	handle_exit_status(int fd, char *line, int *i, t_ma *ma)
{
	char	*exit_status_str;

	if (line[*i] == '$' && line[*i + 1] == '?')
	{
		exit_status_str = ft_itoa_g_c(ma->last_exit_status, &(ma->first_node));
		write(fd, exit_status_str, ft_strlen(exit_status_str));
		*i += 2;
		return (1);
	}
	return (0);
}

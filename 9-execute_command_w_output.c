/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-execute_command_w_output.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:30:21 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/25 01:26:59 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_builtin_echo(t_astnode *node, t_ntc **first_node,
		int is_pipe, int is_redirect, char *output_file)
{
	char	*output;

	output = builtin_echo(node, first_node);
	if (is_pipe)
		return (output);
	if (is_redirect)
		redirect_output(output, output_file);
	else
		ft_printf("%s\n", output);
	free(output);
	return (NULL);
}

static char	*handle_builtin_pwd(t_ntc **first_node, int is_pipe,
		int is_redirect, char *output_file)
{
	char	*output;

	output = builtin_pwd(first_node);
	if (is_pipe)
		return (output);
	if (is_redirect)
		redirect_output(output, output_file);
	else
		ft_printf("%s\n", output);
	free(output);
	return (NULL);
}

static char	*handle_builtin_env(char **env, t_ntc **first_node, int is_pipe,
		int is_redirect, char *output_file)
{
	char	*output;

	output = builtin_env(env, first_node);
	if (is_pipe)
		return (output);
	if (is_redirect)
		redirect_output(output, output_file);
	else
		ft_printf("%s\n", output);
	free(output);
	return (NULL);
}

char	*execute_command_w_output(t_astnode *node, int is_pipe, int is_redirect,
		char *output_file, t_ntc **first_node, char **env)
{
	if (!node)
		return (NULL);
	if (node->data.simple_command.words
		&& strcmp(node->data.simple_command.words->data.word.value,
			"echo") == 0)
		return (handle_builtin_echo(node, first_node, is_pipe, is_redirect,
				output_file));
	if (node->data.simple_command.words
		&& strcmp(node->data.simple_command.words->data.word.value, "pwd") == 0)
		return (handle_builtin_pwd(first_node, is_pipe, is_redirect,
				output_file));
	if (node->data.simple_command.words
		&& strcmp(node->data.simple_command.words->data.word.value, "env") == 0)
		return (handle_builtin_env(env, first_node, is_pipe, is_redirect,
				output_file));
	return (NULL);
}

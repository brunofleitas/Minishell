/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:12:28 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/01 18:25:31 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    node: Pointer to the abstract syntax tree (AST) node.
    first_node: Double pointer to the first node of type t_ntc.
    env: Array of environment variables.
  Return value:
    Returns a string if the command is "echo", "pwd", or "env". 
    Returns NULL otherwise.
  Description:
    Executes the appropriate built-in shell command based on the 
    value of the first word in the simple command of the AST node.
    For "cd", "export", and "unset", the 
    function calls their respective handlers without returning a 
    value. For "echo", "pwd", and "env", the function calls their 
    respective handlers and returns the resulting string.
*/
char	*execute_builtin(t_astnode *node, t_ntc **first_node, char **env)
{
	if (!node)
		return (NULL);
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "cd") == 0)
		return(builtin_cd(node, first_node, env));
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "export") == 0)
		return(builtin_export(node, first_node, env));
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "unset") == 0)
		return(builtin_unset(node, first_node));
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "echo") == 0)
		return(builtin_echo(node, first_node));
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "pwd") == 0)
		return (builtin_pwd(first_node));
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "env") == 0)
		return (builtin_env(env, first_node));
	return (NULL);
}

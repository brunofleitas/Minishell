/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-execute_command_wo_output.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:36:39 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/25 17:36:07 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_command_wo_output(t_astnode *node, int is_pipe, int is_redirect,
		char *output_file, t_ntc **first_node, char **env)
{
	if (!node)
		return (NULL);
	if (node->data.simple_command.words
		&& strcmp(node->data.simple_command.words->data.word.value, "cd") == 0)
		builtin_cd(node, first_node);
	if (node->data.simple_command.words
		&& strcmp(node->data.simple_command.words->data.word.value, "export") == 0)
		builtin_export(node, first_node);
	if (node->data.simple_command.words
		&& strcmp(node->data.simple_command.words->data.word.value, "unset") == 0)
		builtin_unset(node, first_node);
}

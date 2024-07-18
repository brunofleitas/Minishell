/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-execute_simple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:30:21 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/18 23:31:59 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(t_astnode *node)
{    
    if (!node) 
        return;
    if (node->type == NODE_SIMPLE_COMMAND)
        if (node->data.simple_command.words &&
            strcmp(node->data.simple_command.words->data.word.value, "echo") == 0)
            execute_echo(node);
}

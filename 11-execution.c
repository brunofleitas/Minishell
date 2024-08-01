/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19-execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:01:03 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/01 17:59:08 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_astnode *node, t_env *env, t_ntc **first_node)
{
    int leftStatus;
    int rightStatus;

	if (!node)
		return (0);
    if (node->type == NODE_CMD_LINE) 
    {
        leftStatus = execution(node->data.cmd_line.left, env, first_node);
        if (node->data.cmd_line.operator == /*AND*/) 
        {
            if (leftStatus == 1)
            {
                rightStatus = execution(node->data.cmd_line.right, env, first_node);
                return rightStatus;
            }
            return leftStatus;
        }
        else if (node->data.cmd_line.operator == /*OR*/)
        {
            if (leftStatus != 1)
            {
                rightStatus = execution(node->data.cmd_line.right, env, first_node);
                return rightStatus; 
            }
            return leftStatus;
        }
    }
    else if (node->type == NODE_PIPELINE)
    	return(execute_pipeline(node, env, first_node));
    else if (node->type == NODE_SIMPLE_CMD)
    {
        //can we change the creation of the pipeline to handle a simple command?
        // so we can call execute_pipeline(node, env) here
        // and not run fork again
    }
    return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24-AST_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/03 20:01:43 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 @brief Main execution function for the AST

 This function serves as the entry point for executing the Abstract Syntax Tree (AST).
 It determines the type of the node and calls the appropriate execution function.

 @param node Pointer to the current AST node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the executed command
*/
void execute_ast(t_astnode *node, t_ma *ma)
{
    if (!node)
    {
        exit_or_setexit(0, 0, ma);
        return; 
    }
    if (node->type == NODE_CMD_LINE)
        execute_cmd_line(node, ma);
    else if (node->type == NODE_PIPELINE)
        execute_pipeline(node, ma);
    else if (node->type == NODE_SIMPLE_CMD)
        execute_simple_cmd(node, ma);
    else
    {
        ft_printf("%i\n", node->type);
        ft_putstr_fd("Error: Unknown node type\n", STDERR_FILENO);// just an Idea I got if we want a file where we store all the errors
        exit_or_setexit(1, 0, ma);
    }
    return;
}

/**
 @brief Execute a command line node
 This function handles the execution of a command line node, which can contain
 multiple commands connected by AND (&&) or OR (||) operators.

 @param node Pointer to the command line node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the last executed command
 */
void execute_cmd_line(t_astnode *node, t_ma *ma)
{   
    //printf("execute_cmd_line start\n");
    ma->and_or++;
    execute_ast(node->data.cmd_line.left, ma);
    if (node->data.cmd_line.operator == TOKEN_AND)
    {
        if (ma->last_exit_status == 0)
            execute_ast(node->data.cmd_line.right, ma);
        else
        {
            ma->and_or = 0;
            exit_or_setexit(1, 0, ma);
        }
            return;

    }
    else if (node->data.cmd_line.operator == TOKEN_OR)
    {
        if (ma->last_exit_status != 0)
            execute_ast(node->data.cmd_line.right, ma);
        else
        {
            ma->and_or = 0;
            exit_or_setexit(0, 0, ma);
            return;
        }
    }
    //printf("execute_cmd_line end\n");
    return;
}
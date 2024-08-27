/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19-AST_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/19 10:10:34 by bfleitas         ###   ########.fr       */
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
int execute_ast(t_astnode *node, t_ma *ma)
{
    if (!node)
        return (EXIT_SUCCESS);
    if (node->type == NODE_CMD_LINE)
        return (execute_cmd_line(node, ma));
    else if (node->type == NODE_PIPELINE)
        return(execute_pipeline(node, ma));
    else if (node->type == NODE_SIMPLE_CMD)
        return(execute_simple_cmd(node, ma));
    else
    {
        //printf("%i\n", node->type);
        ft_putstr_fd("Error: Unknown node type\n", STDERR_FILENO);// just an Idea I got if we want a file where we store all the errors
        return (EXIT_FAILURE);
    }
}

/**
 @brief Execute a command line node
 This function handles the execution of a command line node, which can contain
 multiple commands connected by AND (&&) or OR (||) operators.

 @param node Pointer to the command line node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the last executed command
 */
int execute_cmd_line(t_astnode *node, t_ma *ma)
{
    int left_result;
    
    //printf("execute_cmd_line start\n");
    left_result = execute_ast(node->data.cmd_line.left, ma);
    if (node->data.cmd_line.operator == TOKEN_AND)
    {
        if (left_result == 0)
            return (execute_ast(node->data.cmd_line.right, ma));
        return (left_result);
    }
    else if (node->data.cmd_line.operator == TOKEN_OR)
    {
        if (left_result != 0)
            return (execute_ast(node->data.cmd_line.right, ma));
        return (left_result);
    }
    //printf("execute_cmd_line end\n");
    return (left_result);
}
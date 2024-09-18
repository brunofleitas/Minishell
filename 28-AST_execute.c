/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28-AST_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:17:52 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the abstract syntax tree (AST) based on the node type.
 *
 * This function executes the AST by determining the type of the current node 
 * and invoking the appropriate execution function for command lines, pipelines, 
 * or simple commands. If the node is NULL, it exits with status 0. If an 
 * unknown node type is encountered, an error message is printed, and the 
 * execution is terminated.
 *
 * @param node Pointer to the current AST node to execute.
 * @param ma Pointer to the structure containing metadata and state for 
 *            execution.
 */
void	execute_ast(t_astnode *node, t_ma *ma)
{
	if (!node)
	{
		exit_or_setexit(0, 0, ma);
		return ;
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
		ft_putstr_fd("Error: Unknown node type\n", STDERR_FILENO);
		exit_or_setexit(1, 0, ma);
	}
	return ;
}

/**
 * @brief Handles the execution of an `AND` (`&&`) operator in a command line.
 *
 * This function executes the right-hand side of an `AND` operator only if 
 * the previous command (left-hand side) was successful (i.e., exit status 
 * is 0). If the left-hand side failed, the function resets the control flow 
 * and exits with status 1.
 *
 * @param node Pointer to the command line AST node containing the `AND` 
 * 			   operator.
 * @param ma Pointer to the structure containing metadata, including the last 
 *           exit status and control flow state.
 */
void	handle_and_operator(t_astnode *node, t_ma *ma)
{
	if (ma->last_exit_status == 0)
	{
		ma->and_or--;
		execute_ast(node->data.cmd_line.right, ma);
	}
	else
	{
		ma->and_or = 0;
		exit_or_setexit(1, 0, ma);
	}
}

/**
 * @brief Handles the execution of an `OR` (`||`) operator in a command line.
 *
 * This function executes the right-hand side of an `OR` operator only if 
 * the previous command (left-hand side) failed (i.e., exit status is not 0). 
 * If the left-hand side succeeded, the function resets the control flow and 
 * exits with status 0.
 *
 * @param node Pointer to the command line AST node containing the `OR` operator.
 * @param ma Pointer to the structure containing metadata, including the last 
 *           exit status and control flow state.
 */
void	handle_or_operator(t_astnode *node, t_ma *ma)
{
	if (ma->last_exit_status != 0)
	{
		ma->and_or--;
		execute_ast(node->data.cmd_line.right, ma);
	}
	else
	{
		ma->and_or = 0;
		exit_or_setexit(0, 0, ma);
	}
}

/**
 * @brief Executes a command line with logical operators (`&&` or `||`).
 *
 * This function executes the left-hand side of a command line containing 
 * logical operators (`&&` or `||`). Based on the result of the left-hand side, 
 * it either executes the right-hand side (for `AND` or `OR`) or terminates 
 * the execution. It uses helper functions to handle the behavior of `AND` 
 * and `OR` operators.
 *
 * @param node Pointer to the command line AST node.
 * @param ma Pointer to the structure containing metadata, including the 
 *           control flow state and last exit status.
 */
void	execute_cmd_line(t_astnode *node, t_ma *ma)
{
	ma->and_or++;
	execute_ast(node->data.cmd_line.left, ma);
	if (node->data.cmd_line.operator == TOKEN_AND)
	{
		handle_and_operator(node, ma);
		return ;
	}
	else if (node->data.cmd_line.operator == TOKEN_OR)
	{
		handle_or_operator(node, ma);
		return ;
	}
}

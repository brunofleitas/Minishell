/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22-AST_parse_cmd_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:50:59 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:11:00 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks the syntax of the command line.
 *
 * This function verifies the syntax of the current token in the command line. 
 * It ensures that the command does not start with an invalid token such as 
 * `&&` or `||`. If a syntax error is detected, it prints an error message 
 * and exits the program.
 *
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing.
 */
void	check_cmd_line_syntax(t_ma *ma)
{
	if (ma->c_tkn == NULL || *(ma->c_tkn) == NULL
		|| ((*(ma->c_tkn))->type == TOKEN_AND
			|| (*(ma->c_tkn))->type == TOKEN_OR))
	{
		write(2, "minishell : syntax error near unexpected token \n", 48);
		exit(1);
	}
}

/**
 * @brief Creates a command line AST node and links its components.
 *
 * This function creates a new command line node in the abstract syntax tree 
 * (AST), setting its left child, operator type, and right child based on the 
 * parsed tokens. It advances to the next token and checks for any syntax 
 * errors before parsing the right-hand side of the pipeline.
 *
 * @param node Pointer to the left child node of the command line node.
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 * @return A pointer to the newly created command line node.
 */
t_astnode	*create_cmd_line_node(t_astnode *node, t_ma *ma)
{
	t_astnode	*new_node;

	new_node = create_ast_node(&(ma->first_node), NODE_CMD_LINE);
	new_node->data.cmd_line.left = node;
	new_node->data.cmd_line.operator = (*(ma->c_tkn))->type;
	get_next_token(ma);
	check_cmd_line_syntax(ma);
	new_node->data.cmd_line.right = parse_pipeline(ma);
	return (new_node);
}

/**
 * @brief Parses a command line into an abstract syntax tree (AST).
 *
 * This function parses a command line into an AST by first checking the 
 * syntax, then parsing a pipeline, and continuing to process logical 
 * operators (`&&` or `||`) as part of the command line structure. It 
 * creates new command line nodes as necessary and returns the root node 
 * of the resulting AST.
 *
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 * @return The root node of the parsed command line AST.
 */
t_astnode	*parse_cmd_line(t_ma *ma)
{
	t_astnode	*node;
	t_astnode	*new_node;

	check_cmd_line_syntax(ma);
	node = parse_pipeline(ma);
	while ((*(ma->c_tkn)) && ((*(ma->c_tkn))->type == TOKEN_AND
			|| (*(ma->c_tkn))->type == TOKEN_OR))
	{
		new_node = create_cmd_line_node(node, ma);
		node = new_node;
	}
	return (node);
}

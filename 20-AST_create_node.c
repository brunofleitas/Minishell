/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15-AST_create_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:26:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 00:44:43 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new AST node of a specified type.
 *
 * This function allocates memory for a new abstract syntax tree (AST) node, 
 * initializes its type, and returns it. If memory allocation fails, it 
 * prints an error message and exits the program.
 *
 * @param first_node Pointer to the first node of the memory allocation chain 
 *                   for garbage collection.
 * @param type The type of the AST node to create.
 * @return A pointer to the newly created AST node.
 */
t_astnode	*create_ast_node(t_ntc **first_node, t_nodetype type)
{
	t_astnode	*node;

	node = g_c(first_node, sizeof(t_astnode))->data;
	if (!node)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		exit(1);
	}
	node->type = type;
	return (node);
}

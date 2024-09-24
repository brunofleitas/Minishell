/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25-AST_parse_simple_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:02:27 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/24 00:19:58 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses a simple command into an abstract syntax tree (AST) node.
 *
 * This function creates a simple command node in the AST, parses the list 
 * of words (arguments) for the command, and handles any redirections 
 * associated with it. It stores the parsed data in the simple command node 
 * and returns it.
 *
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 * @return A pointer to the parsed simple command node in the AST.
 */
t_astnode	*parse_simple_cmd(t_ma *ma)
{
	t_astnode	*node;
	t_astnode	*last_word;

	last_word = NULL;
	node = create_ast_node(&(ma->first_node), NODE_SIMPLE_CMD);
	node->u_data.s_simple_cmd.words = NULL;
	node->u_data.s_simple_cmd.redirections = NULL;
	parse_word_list(node, &last_word, ma);
	parse_redirection_list(node, &last_word, ma);
	return (node);
}

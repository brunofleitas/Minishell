/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24-AST_parse_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:58:55 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:13:27 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses a command into an abstract syntax tree (AST) node.
 *
 * This function parses a command, handling both parenthesized command 
 * groups and simple commands. If an opening parenthesis is found, it parses 
 * a command line and ensures there is a matching closing parenthesis. 
 * Otherwise, it proceeds to parse a simple command.
 *
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 * @return A pointer to the parsed command node in the AST.
 */
t_astnode	*parse_cmd(t_ma *ma)
{
	t_astnode	*node;

	if ((*(ma->c_tkn))->type == TOKEN_LPAREN)
	{
		get_next_token(ma);
		node = parse_cmd_line(ma);
		if ((*(ma->c_tkn)) && (*(ma->c_tkn))->type != TOKEN_RPAREN)
		{
			fprintf(stderr, "Error: Expected closing parenthesis\n");
			exit(1);
		}
		get_next_token(ma);
		return (node);
	}
	else
	{
		return (parse_simple_cmd(ma));
	}
}

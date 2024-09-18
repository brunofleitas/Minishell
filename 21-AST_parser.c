/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14-AST_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:40:58 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 00:43:52 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses the input and constructs the abstract syntax tree (AST).
 *
 * This function initiates the parsing process by calling the command line 
 * parser to build the root node of the abstract syntax tree (AST) based on 
 * the input provided in the `ma` structure.
 *
 * @param ma Pointer to the structure containing metadata for parsing and 
 *           memory allocation.
 * @return The root node of the generated AST.
 */
t_astnode	*parser(t_ma *ma)
{
	t_astnode	*root;

	root = NULL;
	root = parse_cmd_line(ma);
	return (root);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23-AST_parse_pipeline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:54:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/24 00:29:39 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Stores command redirections in a pipeline node.
 *
 * This function reallocates memory for storing redirections associated 
 * with commands in a pipeline node. It sets up the redirection array and 
 * parses the redirection list for the current command in the pipeline. 
 * If memory allocation fails, it prints an error message and exits the program.
 *
 * @param n_pipeline Pointer to the pipeline node in the AST.
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 */
void	store_cmd_redirections(t_astnode *n_pipeline, t_ma *ma)
{
	n_pipeline->u_data.s_pipeline.cmds_redir = ft_realloc_g_c(&(ma->first_node),
			n_pipeline->u_data.s_pipeline.cmds_redir,
			n_pipeline->u_data.s_pipeline.cmd_count * sizeof(t_astnode *));
	n_pipeline->u_data.s_pipeline.cmds_redir \
		[n_pipeline->u_data.s_pipeline.cmd_count - 1] = NULL;
	if (!n_pipeline->u_data.s_pipeline.cmds_redir)
	{
		write(2, "cmd_redir creation failed\n", 13);
		exit(1);
	}
	parse_redirection_list(n_pipeline, NULL, ma);
}

/**
 * @brief Checks for the presence of the next token in the token stream.
 *
 * This function verifies that there is a valid next token in the token stream. 
 * If no token is found, it prints a syntax error message and exits the program.
 *
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing.
 */
void	check_next_token(t_ma *ma)
{
	if (ma->c_tkn == NULL || *(ma->c_tkn) == NULL)
	{
		write(2, "minishell : syntax error near unexpected token \n", 48);
		exit(1);
	}
}

/**
 * @brief Adds a command to an existing pipeline in the AST.
 *
 * This function increments the command count in a pipeline node and 
 * dynamically reallocates memory to store the new command. It parses the 
 * command and adds it to the pipeline, handling any associated redirections 
 * if present.
 *
 * @param node Pointer to the pipeline node in the AST.
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 */
void	add_command_to_pipeline(t_astnode *node, t_ma *ma)
{
	node->u_data.s_pipeline.cmd_count++;
	node->u_data.s_pipeline.cmds = ft_realloc_g_c(&(ma->first_node),
			node->u_data.s_pipeline.cmds, node->u_data.s_pipeline.cmd_count
			* sizeof(t_astnode *));
	node->u_data.s_pipeline.cmds[node->u_data.s_pipeline.cmd_count - 1] \
			= parse_cmd(ma);
	if (*(ma->c_tkn) && is_redirection_token((*(ma->c_tkn))->type))
		store_cmd_redirections(node, ma);
}

/**
 * @brief Parses a pipeline of commands into an abstract syntax tree (AST).
 *
 * This function creates a pipeline node in the AST, parses individual 
 * commands, and adds them to the pipeline. It handles redirections and 
 * pipes (`|`) between commands. The function continues parsing until no 
 * more pipe tokens are found, and it returns the pipeline node.
 *
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 * @return A pointer to the pipeline node in the AST.
 */
t_astnode	*parse_pipeline(t_ma *ma)
{
	t_astnode	*node;

	node = create_ast_node(&(ma->first_node), NODE_PIPELINE);
	node->u_data.s_pipeline.cmds = g_c(&(ma->first_node), \
		sizeof(t_astnode *))->data;
	node->u_data.s_pipeline.cmds[0] = parse_cmd(ma);
	node->u_data.s_pipeline.cmd_count = 1;
	node->u_data.s_pipeline.cmds_redir = NULL;
	if (*(ma->c_tkn) && is_redirection_token((*(ma->c_tkn))->type))
		store_cmd_redirections(node, ma);
	while ((*(ma->c_tkn)) && (*(ma->c_tkn))->type == TOKEN_PIPE)
	{
		get_next_token(ma);
		check_next_token(ma);
		add_command_to_pipeline(node, ma);
	}
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26-AST_parse_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:03:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:54:50 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a token is a redirection token.
 *
 * This function determines whether a given token type represents a 
 * redirection, such as input (`<`), output (`>`), append (`>>`), or heredoc 
 * (`<<`).
 *
 * @param type The type of the token to check.
 * @return 1 if the token is a redirection, 0 otherwise.
 */
int	is_redirection_token(t_token_type type)
{
	int	result;

	result = (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
			|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
	return (result);
}

/**
 * @brief Adds a redirection node to the list of redirections.
 *
 * This function adds a redirection node to the list of redirections for a 
 * command or pipeline. If it's the first redirection, it initializes the list. 
 * Otherwise, it appends the redirection node to the end of the list.
 *
 * @param first_redir_node Pointer to the first redirection node in the list.
 * @param current Pointer to the current redirection node in the list, used 
 *                to append the new redirection.
 * @param redir_node The redirection node to be added to the list.
 */
void	add_redir(t_astnode **first_redir_node, t_astnode **current,
		t_astnode *redir_node)
{
	if (!(*first_redir_node))
	{
		*first_redir_node = redir_node;
		*current = *first_redir_node;
	}
	else
	{
		(*current)->data.redirection.next = redir_node;
		*current = redir_node;
	}
}

/**
 * @brief Checks the syntax of a redirection.
 *
 * This function verifies that the token following a redirection operator 
 * is a valid word (i.e., a filename or argument). If the syntax is invalid, 
 * it prints a syntax error message and exits the program.
 *
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing.
 */
void	check_redirection_syntax(t_ma *ma)
{
	if (ma->c_tkn == NULL || *(ma->c_tkn) == NULL
		|| !is_word_token((*(ma->c_tkn))->type))
	{
		write(2, "minishell : syntax error near unexpected token \n", 48);
		exit(1);
	}
}

/**
 * @brief Processes and adds a redirection to a command or pipeline.
 *
 * This function adds a redirection node to either a simple command or a 
 * command in a pipeline. It checks whether the command is part of a pipeline 
 * or a simple command and links the redirection accordingly.
 *
 * @param node Pointer to the current command or pipeline node in the AST.
 * @param last_word Pointer to the last word node, used to determine whether 
 *                  the command is a simple command or part of a pipeline.
 * @param redir_node Pointer to the redirection node to be added.
 * @param current Pointer to the current redirection node, used to maintain 
 *                the list of redirections.
 */
void	process_redirection(t_astnode *node, t_astnode **last_word,
	t_astnode *redir_node, t_astnode **current)
{
	if (!last_word)
	{
		add_redir(&(node->data.pipeline.cmds_redir[node-> \
		data.pipeline.cmd_count - 1]), current, redir_node);
	}
	else
	{
		add_redir(&(node->data.simple_cmd.redirections), current, redir_node);
	}
}

/**
 * @brief Parses the list of redirections for a command.
 *
 * This function processes and parses redirection tokens (e.g., `<`, `>`, `>>`) 
 * and associates them with the corresponding command in the AST. It checks 
 * for syntax errors, retrieves the file associated with each redirection, 
 * and links the redirection nodes to the command. If additional words 
 * (arguments) are found after redirections, they are parsed as well.
 *
 * @param node Pointer to the command node in the AST.
 * @param last_word Pointer to the last word node in the command's word list.
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 */
void	parse_redirection_list(t_astnode *node, t_astnode **last_word, t_ma *ma)
{
	t_astnode	*current;
	t_astnode	*redir_node;

	current = NULL;
	while ((*(ma->c_tkn)) && is_redirection_token((*(ma->c_tkn))->type))
	{
		redir_node = create_ast_node(&(ma->first_node), NODE_REDIRECTION);
		redir_node->data.redirection.type = (*(ma->c_tkn))->type;
		get_next_token(ma);
		check_redirection_syntax(ma);
		redir_node->data.redirection.file = (*(ma->c_tkn))->value;
		redir_node->data.redirection.next = NULL;
		get_next_token(ma);
		process_redirection(node, last_word, redir_node, &current);
		if ((*(ma->c_tkn)) && is_word_token((*(ma->c_tkn))->type) && last_word)
			parse_word_list(node, last_word, ma);
	}
}

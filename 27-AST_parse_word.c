/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27-AST_parse_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:04:44 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/24 00:21:48 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a token is a word token.
 *
 * This function determines whether a given token type represents a word 
 * token, which includes built-ins, quoted strings, environment variables, 
 * exit status, wildcards, and regular words.
 *
 * @param type The type of the token to check.
 * @return 1 if the token is a word token, 0 otherwise.
 */
int	is_word_token(t_token_type type)
{
	int	result;

	result = (type == TOKEN_BUILTIN || type == TOKEN_SINGLE_QUOTE
			|| type == TOKEN_DOUBLE_QUOTE || type == TOKEN_ENV_VAR
			|| type == TOKEN_EXIT_STATUS || type == TOKEN_WILDCARD
			|| type == TOKEN_WORD);
	return (result);
}

/**
 * @brief Adds a word node to the list of words (arguments) for a command.
 *
 * This function adds a word node to the list of words in a simple command. 
 * If it's the first word, it initializes the list. Otherwise, it appends the 
 * word node to the end of the list and updates the current pointer.
 *
 * @param first_word_node Pointer to the first word node in the list.
 * @param current Pointer to the current word node in the list, used to append 
 *                the new word.
 * @param word_node The word node to be added to the list.
 */
void	add_word(t_astnode **first_word_node, t_astnode **current,
		t_astnode *word_node)
{
	if (!(*first_word_node))
	{
		*first_word_node = word_node;
		*current = *first_word_node;
	}
	else
	{
		(*current)->u_data.s_word.next = word_node;
		*current = word_node;
	}
}

/**
 * @brief Parses a list of words (arguments) for a command.
 *
 * This function processes and parses consecutive word tokens (e.g., arguments) 
 * for a simple command. It creates word nodes for each token and adds them 
 * to the command's word list. The function updates the last word node to 
 * maintain the list of words.
 *
 * @param node Pointer to the simple command node in the AST.
 * @param last_word Pointer to the last word node, used to maintain the 
 *                  current word list.
 * @param ma Pointer to the structure containing the current token and 
 *           metadata for parsing and memory allocation.
 */
void	parse_word_list(t_astnode *node, t_astnode **last_word, t_ma *ma)
{
	t_astnode	*current;
	t_astnode	*word_node;

	if (*last_word)
		current = *last_word;
	else
		current = NULL;
	while ((*(ma->c_tkn)) && is_word_token((*(ma->c_tkn))->type))
	{
		word_node = create_ast_node(&(ma->first_node), NODE_WORD);
		word_node->u_data.s_word.value = (*(ma->c_tkn))->value;
		word_node->u_data.s_word.type = (*(ma->c_tkn))->type;
		word_node->u_data.s_word.next = NULL;
		add_word(&(node->u_data.s_simple_cmd.words), &(current), word_node);
		get_next_token(ma);
	}
	if (current)
		*last_word = current;
}

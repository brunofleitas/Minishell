/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-AST_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:08:01 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/25 07:50:53 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_word_token(t_token_type type)
{
	int	result;

	result = (type == TOKEN_BUILTIN || type == TOKEN_SINGLE_QUOTE
			|| type == TOKEN_DOUBLE_QUOTE || type == TOKEN_ENV_VAR
			|| type == TOKEN_EXIT_STATUS || type == TOKEN_WILDCARD
			|| type == TOKEN_WORD);
	return (result);
}

static int	is_redirection_token(t_token_type type)
{
	int	result;

	result = (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
			|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
	return (result);
}

static void	add_word(t_astnode **first_word_node, t_astnode **current,
		t_astnode *word_node)
{
	if (!(*first_word_node))
	{
		*first_word_node = word_node;
		*current = *first_word_node;
	}
	else
	{
		(*current)->data.word.next = word_node;
		*current = word_node;
	}
}

static void	parse_word_list(t_astnode *node, t_astnode **last_word, t_ma *ma)
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
		word_node->data.word.value = (*(ma->c_tkn))->value;
		word_node->data.word.type = (*(ma->c_tkn))->type;
		word_node->data.word.next = NULL;
		add_word(&(node->data.simple_cmd.words), &(current), word_node);
		get_next_token(ma);
	}
	if (current)
		*last_word = current;
}

static void	add_redir(t_astnode **first_redir_node, t_astnode **current,
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

static void	parse_redirection_list(t_astnode *node, t_astnode **last_word,
		t_ma *ma)
{
	t_astnode	*current_in;
	t_astnode	*current_out;
	t_astnode	*redir_node;

	current_in = NULL;
	current_out = NULL;
	while ((*(ma->c_tkn)) && is_redirection_token((*(ma->c_tkn))->type))
	{
		redir_node = create_ast_node(&(ma->first_node), NODE_REDIRECTION);
		redir_node->data.redirection.type = (*(ma->c_tkn))->type;
		get_next_token(ma);
		if ((*(ma->c_tkn)) && !is_word_token((*(ma->c_tkn))->type))
		{
			fprintf(stderr, "Error: Expected filename after redirection\n");
			exit(1);
		}
		redir_node->data.redirection.file = (*(ma->c_tkn))->value;
		redir_node->data.redirection.next = NULL;
		get_next_token(ma);
		if (redir_node->data.redirection.type == TOKEN_REDIR_IN
			|| redir_node->data.redirection.type == TOKEN_HEREDOC)
			add_redir(&(node->data.simple_cmd.redirections_in), &(current_in),
				redir_node);
		else
			add_redir(&(node->data.simple_cmd.redirections_out), &(current_out),
				redir_node);
		if ((*(ma->c_tkn)) && is_word_token((*(ma->c_tkn))->type))
			parse_word_list(node, last_word, ma);
	}
}

static t_astnode	*parse_simple_cmd(t_ma *ma)
{
	t_astnode	*node;
	t_astnode	*last_word;

	last_word = NULL;
	node = create_ast_node(&(ma->first_node), NODE_SIMPLE_CMD);
	node->data.simple_cmd.words = NULL;
	node->data.simple_cmd.redirections_in = NULL;
	node->data.simple_cmd.redirections_out = NULL;
	parse_word_list(node, &last_word, ma);
	parse_redirection_list(node, &last_word, ma);
	return (node);
}

static t_astnode	*parse_cmd(t_ma *ma)
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

static t_astnode	*parse_pipeline(t_ma *ma)
{
	t_astnode	*node;

	node = create_ast_node(&(ma->first_node), NODE_PIPELINE);
	node->data.pipeline.cmds = g_c(&(ma->first_node),
			sizeof(t_astnode *))->data;
	node->data.pipeline.cmds[0] = parse_cmd(ma);
	node->data.pipeline.cmd_count = 1;
	while (((*(ma->c_tkn))) && (*(ma->c_tkn))->type == TOKEN_PIPE)
	{
		get_next_token(ma);
		node->data.pipeline.cmd_count++;
		node->data.pipeline.cmds = ft_realloc_g_c(&(ma->first_node),
				node->data.pipeline.cmds, node->data.pipeline.cmd_count
				* sizeof(t_astnode *));
		node->data.pipeline.cmds[node->data.pipeline.cmd_count
			- 1] = parse_cmd(ma);
	}
	return (node);
}

t_astnode	*parse_cmd_line(t_ma *ma)
{
	t_astnode	*node;
	t_astnode	*new_node;

	node = parse_pipeline(ma);
	while ((*(ma->c_tkn)) && ((*(ma->c_tkn))->type == TOKEN_AND
			|| (*(ma->c_tkn))->type == TOKEN_OR))
	{
		new_node = create_ast_node(&(ma->first_node), NODE_CMD_LINE);
		new_node->data.cmd_line.left = node;
		new_node->data.cmd_line.operator = (*(ma->c_tkn))->type;
		get_next_token(ma);
		new_node->data.cmd_line.right = parse_pipeline(ma);
		node = new_node;
	}
	return (node);
}

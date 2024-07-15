/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:26:55 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/15 23:46:47 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
	token: A pointer to a t_word structure representing the current token.
	first_node: A double pointer to a t_ntc structure.
  Return value:
	A pointer to a t_ast structure, representing the newly created AST node.
  Description:
	Creates a new AST node with the given token. Initializes the left and
    right children to NULL.
*/
static t_ast	*create_new_node(t_word *token, t_ntc **first_node)
{
	t_ast	*node;

	node = g_c(first_node, sizeof(t_ast))->data;
	node->data = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/*
  Parameters:
    root: A pointer to a t_ast structure representing the root of the AST.
    token: A pointer to a t_word structure representing the current token.
    first_node: A double pointer to a t_ntc structure.
  Return value:
    A pointer to a t_ast structure, representing the updated AST.
  Description:
    Inserts a new AST node with the given token into the AST.
    If the root is NULL, creates a new node with the given token.
    Otherwise, recursively inserts the node into the left or right subtree
    based on the token type.
*/
static t_ast	*insert_ast_node(t_ast *root, t_word *token, t_ntc **first_node)
{
	if (root == NULL)
		return (create_new_node(token, first_node));
	if (is_command(token))
	{
		root->left = insert_ast_node(root->left, token, first_node);
		return (root);
	}
	if (is_operator(token))
	{
		root->right = insert_ast_node(root->right, token, first_node);
		return (root);
	}
	if (is_redirect(token))
	{
		root->right = insert_ast_node(root->right, token, first_node);
		return (root);
	}
	if (is_variable(token))
	{
		root->right = insert_ast_node(root->right, token, first_node);
		return (root);
	}
	if (is_string(token))
	{
		root->right = insert_ast_node(root->right, token, first_node);
		return (root);
	}
	if (is_argument(token))
	{
		root->right = insert_ast_node(root->right, token, first_node);
		return (root);
	}
	if (is_here_document(token))
	{
		root->right = insert_ast_node(root->right, token, first_node);
		return (root);
	}
	if (is_error(token))
	{
		root->right = insert_ast_node(root->right, token, first_node);
		return (root);
	}
	return (root);
}

/*
  Parameters:
    tokens: A double pointer to a t_word structure representing the tokens.
    root: A double pointer to a t_ast structure representing the root of the AST.
    first_node: A double pointer to a t_ntc structure.
  Return value:
    None.
  Description:
    Builds the AST by inserting each token into the AST.
*/
static void	build_ast(t_word **tokens, t_ast **root, t_ntc **first_node)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		*root = insert_ast_node(*root, tokens[i], first_node);
		i++;
	}
}

/*
  Parameters:
    root: A pointer to a t_ast structure representing the root of the AST.
  Return value:
    None.
  Description:
    Prints the AST in an in-order traversal.
*/
static void	print_ast(t_ast *root)
{
	if (root == NULL)
		return ;
	print_ast(root->left);
	ft_printf("%s\n", root->data->value);
	print_ast(root->right);
}

/*
  Parameters:
    tokens: A double pointer to a t_word structure representing the tokens.
    root: A double pointer to a t_ast structure representing the root of the AST.
    first_node: A double pointer to a t_ntc structure.
  Return value:
    None.
  Description:
    Parses the tokens and builds the AST. Prints the AST.
*/
void	parser(t_word **tokens, t_ast **root, t_ntc **first_node)
{
	build_ast(tokens, root, first_node);
	print_ast(*root);
}

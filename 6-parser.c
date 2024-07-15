/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:26:55 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/15 18:02:22 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast   *create_new_node(t_word *token, t_ntc **first_node)
{
    t_ast   *node;

    node = g_c(first_node, sizeof(t_ast))->data;
    node->data = token;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

static t_ast *insert_ast_node(t_ast *root, t_word *token, t_ntc **first_node)
{
    if (!root)
        return create_new_node(token, first_node);
    if (token->key == TOKEN_COMMAND_ECHO || token->key == TOKEN_COMMAND_CD || token->key == TOKEN_COMMAND_PWD || token->key == TOKEN_COMMAND_EXPORT || token->key == TOKEN_COMMAND_UNSET || token->key == TOKEN_COMMAND_ENV)
        root->left = insert_ast_node(root->left, token, first_node);
    else if (token->key == TOKEN_ARGUMENT) 
        root->right = insert_ast_node(root->right, token, first_node);
    return root;
}

static void build_ast(t_word **tokens, t_ast **root, t_ntc **first_node)
{
    int i = 0;
    while (tokens[i] != NULL)
    {
        *root = insert_ast_node(*root, tokens[i], first_node);
        i++;
    }
}

static void    print_ast(t_ast *root)
{
    if (root == NULL)
        return ;
    print_ast(root->left);
    ft_printf("%s\n", root->data->value);
    print_ast(root->right);
}

void    parser(t_word **tokens, t_ast **root, t_ntc **first_node)
{
    build_ast(tokens, root, first_node);
    print_ast(*root);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-node_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:26:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/18 12:38:59 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astnode *create_ast_node(t_ntc **first_node, t_nodetype type) 
{
    t_astnode *node;
    
    node = g_c(first_node, sizeof(t_astnode))->data;
    if (!node)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    node->type = type;
    return (node);
}

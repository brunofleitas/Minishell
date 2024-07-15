/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8-free_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:56:43 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/16 00:00:13 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    root: A pointer to a pointer to the root of the abstract syntax tree.
  Return value:
    None. This function does not return a value; instead, it frees the memory
      allocated for the abstract syntax tree.
  Description:
    This function recursively frees the memory allocated for the abstract syntax
    tree by traversing the tree in a post-order fashion.
*/
void    free_ast(t_ast **root)
{
    if (*root == NULL)
        return ;
    free_ast(&(*root)->left);
    free_ast(&(*root)->right);
    free((*root)->data->value);
    free((*root)->data);
    free(*root);
    *root = NULL;
}

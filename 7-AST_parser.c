/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-AST_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:40:58 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/13 15:57:00 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_astnode *parser(t_ma *ma)
{
    t_astnode   *root;

    root = NULL;
    root = parse_cmd_line(ma);
    return (root);
}
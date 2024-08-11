/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-AST_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:40:58 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/11 23:21:39 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_astnode *parser(t_ntc **first_node, t_token **tkns) 
{
    t_token     *c_tkn;
    t_astnode   *cmd_line;

    //printf("parser start\n");
    c_tkn = NULL;
    c_tkn = get_next_token(tkns, 1);
    cmd_line = parse_cmd_line(first_node, c_tkn, tkns);
    //printf("parser ends\n");
    return (cmd_line);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-execute_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:20:11 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/18 23:32:09 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_echo(t_astnode *node)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    if (node->data.simple_cmd.word_count > 1 && !ft_strcmp(node->data.simple_cmd.words[1], "-n"))
    {
        newline = 0;
        i++;
    }
    while (i < node->data.simple_cmd.word_count)
    {
        ft_putstr_fd(node->data.simple_cmd.words[i], 1);
        if (i < node->data.simple_cmd.word_count - 1)
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", 1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:59:46 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/09 17:37:49 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *input;

    while (1)
    {
        input = readline(">>");    
        if (input)
        {
            if (strcmp(input, "exit") == 0)
            {
                free(input);
                break;
            }
            add_history(input);
            lexer(input);
            free(input);
        } 
        else
            break;
    }
    rl_clear_history();
    return (0);
}
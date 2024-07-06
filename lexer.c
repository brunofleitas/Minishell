/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:03:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/06 12:24:19 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    lexer(int argc, char **argv)
{
    t_word  *tokens;
    char    **split;
    int i;
    int j;

    i = 0;
    tokens = malloc(sizeof(t_word) * argc);
    while (i < argc)
    {
        split = ft_split(argv[i], ' ');
        j = 0;
        while (split[j])
        {
            tokens[i].value[j] = split[j];
            j++;
        }
        free(split); 
        i++;
    }
    
    for (i = 0; i < argc; i++)  
    {
        for (j = 0; tokens[i].value[j]; j++)
            printf("%s ", tokens[i].value[j]);
        printf("\n");
    }    
}
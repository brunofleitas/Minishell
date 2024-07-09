/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:03:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/09 17:44:29 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    lexer(char *input)
{
    t_word  *tokens[1024];
    char    **split;
    int i;

    i = 0;
    //tokens = malloc(sizeof(t_word) * count_words(input, ' '));
    split = ft_split(input, ' ');
    while (split[i])
    {
        tokens[i]->value = split[i];
        //tokens[i]->key = get_key(tokens[i]->value);
        printf("%s\n", tokens[i]->value);
        i++;
    }
    free(split);
    
    /*
    for (i = 0; i < argc; i++)  
    {
        for (j = 0; tokens[i].value[j]; j++)
            printf("%s ", tokens[i].value[j]);
        printf("\n");
    }*/   
}
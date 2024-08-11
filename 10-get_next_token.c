/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-get_next_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:53 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/11 13:07:55 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *get_next_token(t_token **tkns, int t) 
{
    static int i;

    if (t == 0)
    {
        i = 0;
        return  (NULL);
    }
    if (!tkns[i])
    {
        return (NULL);
    }
    return (tkns[i++]);
}
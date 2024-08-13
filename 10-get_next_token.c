/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-get_next_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:53 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/13 17:13:48 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    get_next_token(t_ma *ma) 
{
    if (ma->c_tkn)
    {
        //printf("token : %s\n", ma->c_tkn[0]->value);
        ma->c_tkn++;
    }
    else
        printf("No more tokens\n");
}
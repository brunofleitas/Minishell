/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16-get_next_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:53 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 00:46:06 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Advances to the next token in the token stream.
 *
 * This function increments the current token pointer, moving to the next 
 * token in the token stream if one exists.
 *
 * @param ma Pointer to the structure containing metadata, including the 
 *           current token.
 */
void	get_next_token(t_ma *ma)
{
	if (ma->c_tkn)
	{
		ma->c_tkn++;
	}
}

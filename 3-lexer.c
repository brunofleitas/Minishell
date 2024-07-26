/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:03:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/11 23:37:17 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    input: String to process.
  Return value:
    None. Modifies the input string and allocates memory for nodes.
  Description:
    Splits the input string into tkns. Stores each word in a new
    node of type t_token. Prints each word and frees split memory.
*/
void	lexer(char *input,t_token **tkns, t_ntc **first_node)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split_tkns(input, ' ', first_node);
	while (split[i])
	{
		tkns[i] = g_c(first_node, sizeof(t_token))->data;
		tkns[i]->value = split[i];
		tkns[i]->type = clasify_token(tkns[i]->value);
		ft_printf("%s\nType : %i\n\n", tkns[i]->value, tkns[i]->type);
		//free_ntc_prior(first_node, split[i]);
		i++;
	}
	free_ntc_prior(first_node, split);
	//free(split);
}

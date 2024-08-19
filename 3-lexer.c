/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:03:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/19 10:10:53 by bfleitas         ###   ########.fr       */
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
void	lexer(t_ma *ma)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split_tkns(' ', ma);
	while (split[i])
	{
		ma->tkns[i] = g_c(&(ma->first_node), sizeof(t_token))->data;
		ma->tkns[i]->value = split[i];
		ma->tkns[i]->type = clasify_token(ma->tkns[i]->value);
		//ft_printf("%s\nType : %i\n\n", ma->tkns[i]->value, ma->tkns[i]->type);
		i++;
	}
	ma->tkns[i] = NULL;
	ma->c_tkn = ma->tkns;
	free_ntc_prior(&(ma->first_node), split);
}

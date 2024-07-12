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
    Splits the input string into tokens. Stores each word in a new
    node of type t_word. Prints each word and frees split memory.
*/
void	lexer(char *input)
{
	t_word	*tokens[1024];
	char	**split;
	int		i;

	i = 0;
	split = ft_split_tokens(input, ' ');
	while (split[i])
	{
		tokens[i] = malloc(sizeof(t_word));
		tokens[i]->value = split[i];
		tokens[i]->key = clasify_token(tokens[i]->value);
		ft_printf("%s\nType : %i\n\n", tokens[i]->value, tokens[i]->key);
		i++;
	}
	free(split);
}

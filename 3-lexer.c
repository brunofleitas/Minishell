/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:03:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 01:00:12 by bfleitas         ###   ########.fr       */
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
	char	**wildcards;
	int		i;
	char   *trimmed;
	// char   *trimmed_dq;

	i = 0;
	split = ft_split_tkns(' ', ma);
	// printf("Split: %s\n", split[0]);
	// printf("Split: %s\n", split[1]);
	if (split[0])
	{
		wildcards = expand_wildcards_in_args(split, ma);
		//printf("Wildcards: %s\n", wildcards[0]);
		//printf("Wildcards: %s\n", wildcards[1]);
		while (wildcards[i])
		{
			ma->tkns[i] = g_c(&(ma->first_node), sizeof(t_token))->data;
			ma->tkns[i]->type = clasify_token(wildcards[i]);
			//printf("Type : %i\n", ma->tkns[i]->type);
			if (wildcards[i][0] == '\"')
				trimmed = ft_strtrim(wildcards[i], "\"", &(ma->first_node));
			else if (wildcards[i][0] == '\'')
				trimmed = ft_strtrim(wildcards[i], "\'", &(ma->first_node));
			else
				trimmed = wildcards[i];
			ma->tkns[i]->value = trimmed;
			//ma->tkns[i]->type = clasify_token(ma->tkns[i]->value);
			//ft_printf("%s\nType : %i\n\n", ma->tkns[i]->value, ma->tkns[i]->type);
			i++;
		}
		ma->tkns[i] = NULL;
		ma->c_tkn = ma->tkns;
	}
	free_ntc_prior(&(ma->first_node), split);
}

// void lexer(t_ma *ma)
// {
//     char    **wildcards;
//     char    **split;
//     int     i;
//     char    *wildcard_pos;

//     i = 0;
//     split = ft_split_tkns(' ', ma);
//     while (split[i])
//     {
//         if ((split[i][0] == '\"' || split[i][0] == '\'') && (wildcard_pos = ft_strchr(split[i], '*')))
//         {
//             // Temporarily replace wildcard with space
//             *wildcard_pos = ' ';

//             // Re-split the string into before, wildcard, and after
//             char **temp_split = ft_split_tkns('*', split[i]);

//             // Replace the current token with the first part
//             split[i] = temp_split[0];
            
//             // Insert the remaining parts into split array
//             int j = 1;
//             while (temp_split[j])
//             {
//                 split = ft_realloc(split, (i + j + 1) * sizeof(char *));
//                 split[i + j] = temp_split[j];
//                 j++;
//             }

//             // Free the temporary split array (only the array itself, not the strings)
//             free(temp_split);

//             // Adjust the loop counter
//             i += (j - 1);
//         }
//         i++;
//     }

//     wildcards = expand_wildcards_in_args(split, ma);
//     i = 0;
//     while (wildcards[i])
//     {
//         ma->tkns[i] = g_c(&(ma->first_node), sizeof(t_token))->data;
//         ma->tkns[i]->value = wildcards[i];
//         ma->tkns[i]->type = clasify_token(ma->tkns[i]->value);
//         ft_printf("%s\nType : %i\n\n", ma->tkns[i]->value, ma->tkns[i]->type);
//         i++;
//     }
//     ma->tkns[i] = NULL;
//     ma->c_tkn = ma->tkns;
//     free_ntc_prior(&(ma->first_node), split);
// }


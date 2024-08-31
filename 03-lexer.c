/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:03:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/30 23:50:19 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Trims quotes from a wildcard string.
 *
 * This function checks if the given wildcard string starts with a double
 * quote or a single quote. If it does, it trims the quotes from the
 * wildcard string using the ft_strtrim function and returns the trimmed
 * string. If the wildcard does not start with a quote, it returns the
 * original wildcard string.
 *
 * @param wildcard The wildcard string to be trimmed.
 * @param ma Pointer to the t_ma structure containing the first_node for
 *           memory management.
 * @return char* The trimmed wildcard string or the original wildcard
 *               string if no quotes were found.
 */
static char	*trim_wildcard(char *wildcard, t_ma *ma)
{
	if (wildcard[0] == '\"')
		return (ft_strtrim(wildcard, "\"", &(ma->first_node)));
	else if (wildcard[0] == '\'')
		return (ft_strtrim(wildcard, "\'", &(ma->first_node)));
	return (wildcard);
}

/**
 * @brief Processes wildcard tokens and stores them in the t_ma structure.
 *
 * This function iterates through the array of wildcard strings, classifies
 * each token, trims any quotes from the wildcard strings, and stores the
 * resulting tokens in the t_ma structure.
 *
 * @param wildcards Array of wildcard strings to be processed.
 * @param ma Pointer to the t_ma structure where the tokens will be stored.
 */
static void	process_wildcards(char **wildcards, t_ma *ma)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (wildcards[i])
	{
		ma->tkns[i] = g_c(&(ma->first_node), sizeof(t_token))->data;
		ma->tkns[i]->type = clasify_token(wildcards[i]);
		trimmed = trim_wildcard(wildcards[i], ma);
		ma->tkns[i]->value = trimmed;
		// printf("%s\n", ma->tkns[i]->value);
		// printf("%i\n", ma->tkns[i]->type);
		i++;
	}
	ma->tkns[i] = NULL;
	ma->c_tkn = ma->tkns;
}

/**
 * @brief Tokenizes the input string and processes wildcards.
 *
 * This function splits the input string into tokens based on spaces,
 * expands any wildcards in the tokens, processes the wildcard tokens,
 * and stores the resulting tokens in the t_ma structure.
 *
 * @param ma Pointer to the t_ma structure containing the input string and
 *           where the tokens will be stored.
 */
void	lexer(t_ma *ma)
{
	char	**split;
	char	**wildcards;

	split = ft_split_tkns(' ', ma);
	if (split[0])
	{
		wildcards = expand_wildcards_in_args(split, ma);
		process_wildcards(wildcards, ma);
	}
	else 
	{
		ma->tkns[0] = NULL;
		ma->c_tkn = ma->tkns;
	}
	free_ntc_prior(&(ma->first_node), split);
}

/*
void	lexer(t_ma *ma)
{
	char	**split;
	char	**wildcards;
	int		i;
	char	*trimmed;

	i = 0;
	split = ft_split_tkns(' ', ma);
	if (split[0])
	{
		wildcards = expand_wildcards_in_args(split, ma);
		while (wildcards[i])
		{
			ma->tkns[i] = g_c(&(ma->first_node), sizeof(t_token))->data;
			ma->tkns[i]->type = clasify_token(wildcards[i]);
			if (wildcards[i][0] == '\"')
				trimmed = ft_strtrim(wildcards[i], "\"", &(ma->first_node));
			else if (wildcards[i][0] == '\'')
				trimmed = ft_strtrim(wildcards[i], "\'", &(ma->first_node));
			else
				trimmed = wildcards[i];
			ma->tkns[i]->value = trimmed;
			i++;
		}
		ma->tkns[i] = NULL;
		ma->c_tkn = ma->tkns;
	}
	free_ntc_prior(&(ma->first_node), split);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04-lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:03:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 03:52:08 by bfleitas         ###   ########.fr       */
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
char	*trim_wildcard(char *wildcard, t_ma *ma, t_token_type type)
{
	if (!(type == 2 && ft_strchr(wildcard, '"') && ft_strchr(wildcard, '*')))
	{
		{
			if (wildcard[0] == '\"')
				return (ft_strtrim_g_c(wildcard, "\"", &(ma->first_node)));
			else if (wildcard[0] == '\'')
				return (ft_strtrim_g_c(wildcard, "\'", &(ma->first_node)));
		}
	}
	if (ft_strcmp(wildcard, "\"*\"") == 0)
	{
		if (wildcard[0] == '\"')
			return (ft_strtrim_g_c(wildcard, "\"", &(ma->first_node)));
		else if (wildcard[0] == '\'')
			return (ft_strtrim_g_c(wildcard, "\'", &(ma->first_node)));
	}
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
void	process_wildcards(char **wildcards, t_ma *ma)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (wildcards[i])
	{
		ma->tkns[i] = g_c(&(ma->first_node), sizeof(t_token))->data;
		ma->tkns[i]->type = clasify_token(wildcards[i]);
		trimmed = trim_wildcard(wildcards[i], ma, ma->tkns[i]->type);
		ma->tkns[i]->value = trimmed;
		i++;
	}
	ma->tkns[i] = NULL;
	ma->c_tkn = ma->tkns;
}

/**
 * handle_ambiguous_redirect - Checks for ambiguous redirection in the input.
 * @split: An array of strings representing the split input.
 *
 * This function iterates through the split input and checks for cases where
 * there is a redirection operator ("<" or "<<") followed by an asterisk ("*").
 * If such a case is found, it writes an error message to the standard error
 * output indicating an ambiguous redirect and returns 1. If no such case is
 * found, it returns 0.
 *
 * Return: 1 if an ambiguous redirect is found, 0 otherwise.
 */
int	handle_ambiguous_redirect(char **split)
{
	int	i;

	i = 0;
	while (split[i] && split[i + 1])
	{
		if ((strcmp(split[i], "<") == 0 || strcmp(split[i], "<<") == 0)
			&& (strcmp(split[i + 1], "*") == 0))
		{
			write(2, "minishell: ", 11);
			write(2, split[i + 1], ft_strlen(split[i + 1]));
			write(2, ": ambiguous redirect\n", 21);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Handles the case where a single wildcard character '*' is present in
 * the input.
 *
 * This function checks if the input split contains only a single wildcard
 * character '*'. If so, it expands the wildcard using the
 * expand_wildcards_in_args function and processes the resulting wildcards. If
 * the expanded wildcard is still '*', the function returns. Otherwise, it
 * prints the first expanded wildcard and exits the program.
 *
 * @param split An array of strings representing the input split.
 * @param ma A pointer to a t_ma structure containing relevant data for
 * processing.
 */
void	handle_single_wildcard(char **split, t_ma *ma)
{
	char	**wildcards;

	if (split[0] && (!split[1]) && strcmp(split[0], "*") == 0)
	{
		wildcards = expand_wildcards_in_args(split, ma);
		process_wildcards(wildcards, ma);
		if (ft_strcmp(wildcards[0], "*") == 0)
			return ;
		printf("%s\n", wildcards[0]);
		exit(0);
	}
}

/**
 * @brief Lexer function to process and tokenize input commands.
 *
 * This function splits the input commands, handles ambiguous redirects,
 * processes single wildcards, and expands wildcards in arguments. If no
 * tokens are found, it sets the token pointers to NULL and exits or sets
 * the exit status.
 *
 * @param ma Pointer to the main structure containing input commands and tokens.
 */
void	lexer(t_ma *ma)
{
	char	**split;
	char	**wildcards;

	split = ft_split_tkns(' ', ma);
	if (handle_ambiguous_redirect(split))
		return ;
	handle_single_wildcard(split, ma);
	if (split[0])
	{
		wildcards = expand_wildcards_in_args(split, ma);
		process_wildcards(wildcards, ma);
	}
	else
	{
		ma->tkns[0] = NULL;
		ma->c_tkn = ma->tkns;
		exit_or_setexit(0, 0, ma);
	}
	free_ntc_prior(&(ma->first_node), split);
}

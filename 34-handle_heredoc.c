/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34-handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 03:57:01 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 02:14:03 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Fills the heredoc delimiters array with values from the token list.
 *
 * This function iterates through the token list and fills the allocated 
 * heredoc delimiters array with the values of the heredoc tokens. It 
 * increments the heredoc flag counter for each heredoc found. If a heredoc 
 * token is found without a following delimiter, the function returns early.
 *
 * @param delimiters_h Pointer to the array of heredoc delimiters to be filled.
 * @param heredoc_f Pointer to the heredoc flag counter, which tracks active 
 *                  heredocs.
 * @param ma Pointer to the structure containing the list of tokens and 
 *           memory management.
 */
void	fill_delimiters(char ***delimiters_h, int *heredoc_f, t_ma *ma)
{
	t_token	**temp;
	int		i;

	temp = ma->tkns;
	i = 0;
	while (temp[0])
	{
		if (temp[0]->type == TOKEN_HEREDOC && temp[1])
		{
			temp++;
			delimiters_h[0][i] = ft_strdup_g_c(temp[0]->value,
					&(ma->first_env));
			(*heredoc_f)++;
			i++;
		}
		else if (temp[0]->type == TOKEN_HEREDOC && !temp[1])
			return ;
		temp++;
	}
	delimiters_h[0][i] = NULL;
}

/**
 * @brief Allocates memory for heredoc delimiters.
 *
 * This function allocates memory for storing the heredoc delimiters, ensuring 
 * there is enough space to hold all delimiters based on the number of heredocs 
 * found. The memory is allocated using `ft_calloc_g_c` for garbage collection.
 *
 * @param delimiters_h Pointer to the array of heredoc delimiters to be 
 * 					   allocated
 * @param heredoc_count The number of heredoc delimiters to allocate space for.
 * @param ma Pointer to the structure containing memory management.
 */
void	allocate_delimiters(char ***delimiters_h, int heredoc_count, t_ma *ma)
{
	*delimiters_h = ft_calloc_g_c(heredoc_count + 1, sizeof(char *),
			&(ma->first_env));
}

/**
 * @brief Counts the number of heredoc tokens in the parsed input.
 *
 * This function iterates through the token list and counts the number of 
 * heredoc tokens (`<<`) present. The count is used to determine how many 
 * heredoc delimiters need to be handled.
 *
 * @param ma Pointer to the structure containing the list of tokens.
 * @return The number of heredoc tokens found in the input.
 */
int	count_heredocs(t_ma *ma)
{
	t_token	**temp;
	int		heredoc_count;

	heredoc_count = 0;
	temp = ma->tkns;
	while (temp[0])
	{
		if (temp[0]->type == TOKEN_HEREDOC)
			heredoc_count++;
		temp++;
	}
	return (heredoc_count);
}

/**
 * @brief Initializes and fills heredoc delimiters for heredoc processing.
 *
 * This function checks for active heredocs, allocates memory for the list 
 * of heredoc delimiters, and populates the list with the relevant delimiters 
 * from the parsed input.
 *
 * @param delimiters_h Pointer to the array of heredoc delimiters.
 * @param heredoc_f Pointer to the heredoc flag counter, which tracks active 
 * 					heredocs.
 * @param ma Pointer to the structure containing parsed input and memory 
 * 			 management.
 */
void	heredoc_checker(char ***delimiters_h, int *heredoc_f, t_ma *ma)
{
	int	heredoc_count;

	heredoc_count = count_heredocs(ma);
	if (heredoc_count == 0)
		return ;
	allocate_delimiters(delimiters_h, heredoc_count, ma);
	fill_delimiters(delimiters_h, heredoc_f, ma);
}

/**
 * @brief Closes a heredoc when the matching delimiter is found.
 *
 * This function searches through the list of heredoc delimiters for a match 
 * with the current input. If a matching delimiter is found, it replaces the 
 * delimiter with an empty string and decreases the heredoc flag counter.
 *
 * @param delimiters_h Pointer to the array of heredoc delimiters.
 * @param heredoc_f Pointer to the heredoc flag counter, which tracks active 
 * 					heredocs.
 * @param ma Pointer to the structure containing the current input and memory 
 * 			 management.
 */
void	close_heredoc(char ***delimiters_h, int *heredoc_f, t_ma *ma)
{
	int	j;

	j = 0;
	if (ma->input && *delimiters_h && delimiters_h[0][j])
	{
		while (delimiters_h[0] && delimiters_h[0][j])
		{
			if (ft_strcmp(ma->input, delimiters_h[0][j]) == 0)
			{
				delimiters_h[0][j] = ft_strdup_g_c("", &(ma->first_env));
				(*heredoc_f)--;
				return ;
			}
			j++;
		}
	}
}

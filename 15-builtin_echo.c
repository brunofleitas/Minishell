/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15-builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:50:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/19 22:05:58 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    node: Pointer to the AST node.
  Return value:
    Returns 0 if the "-n" flag is present, 1 otherwise.
  Description:
    Checks if the "-n" flag is present in the second word of the 
    simple command. If the flag is present, indicates that a newline 
    should not be added after the command output.
*/
static int	should_add_newline(char **args, int word_count)
{
	if (word_count > 1 && !(ft_strncmp(args[1], "-n", 2)))
		return (0);
	return (1);
}

/*
  Parameters:
    node: Pointer to the AST node.
    first_node: Double pointer to the first t_ntc node.
    i: Starting index of the words to join.
  Return value:
    Pointer to the concatenated string of words.
  Description:
    Joins the words from the simple command in the AST node into 
    a single string, starting from the given index. Adds a space 
    between each word. Handles memory allocation and errors.
*/
static char	*join_words(char **args, t_ntc **first_node, int i, int word_count)
{
	char	*result;
	char	*temp;
	char	*actual_arg;

	result = ft_strdup_g_c("", first_node);
	while (i < word_count)
	{
		if (args[i][0] == '\'')
			actual_arg = ft_strtrim(args[i], "'", first_node);
		else if (args[i][0] == '\"')
			actual_arg = ft_strtrim(args[i], "\"", first_node);
		else
			actual_arg = ft_strdup_g_c(args[i], first_node);
		temp = ft_strjoin_g_c(result, actual_arg, first_node);
		result = temp;
		if (i < word_count - 1 || args[i][0] == '\'' || args[i][0] == '\"')
		{
			temp = ft_strjoin_g_c(result, " ", first_node);
			result = temp;
		}
		i++;
	}
	return (result);
}

/*
  Parameters:
    env: Pointer to the environment variables.
    name: Name of the variable to unset.
  Return value:
    Returns 0.
  Description:
    Unsets (removes) an environment variable. Finds the variable 
    by name, frees its memory, shifts the subsequent variables in 
    the array, and decreases the environment variable count.
*/
int	builtin_echo(char **args, int word_count, t_ma *ma)
{
	int		newline;
	int		i;
	char	*result;
	char	*temp;

	newline = should_add_newline(args, word_count);
	if (newline)
		i = 1;
	else
		i = 2;
	result = join_words(args, &(ma->first_node), i, word_count);
	if (newline)
	{
		temp = ft_strjoin_g_c(result, "\n", &(ma->first_node));
		//free_ntc_prior(first_node, result);
		result = temp;
	}
	if (result)
	{
		printf("%s", result);
		//free_ntc_prior(first_node, result);
		return (0);
	}
	return (1);
}

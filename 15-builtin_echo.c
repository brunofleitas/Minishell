/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15-builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:50:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/01 18:18:10 by bfleitas         ###   ########.fr       */
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
static int	should_add_newline(t_astnode *node)
{
	if (node->data.simple_cmd.word_count > 1
		&& !strcmp(node->data.simple_cmd.words->data.word.value[1], "-n"))
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
static char	*join_words(t_astnode *node, t_ntc **first_node, int i)
{
	char	*result;
	char	*temp;

	result = ft_strdup("", first_node);
	while (i < node->data.simple_cmd.word_count)
	{
		temp = ft_strjoin(result, node->data.simple_cmd.words[i],
				first_node);
		free(result);
		result = temp;
		if (i < node->data.simple_cmd.word_count - 1)
		{
			temp = ft_strjoin(result, " ", first_node);
			free(result);
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
char	*builtin_echo(t_astnode *node, t_ntc **first_node)
{
	int		newline;
	int		i;
	char	*result;
	char	*temp;

	newline = should_add_newline(node);
	if (newline)
		i = 1;
	else
		i = 2;
	result = join_words(node, first_node, i);
	if (newline)
	{
		temp = ft_strjoin(result, "\n", first_node);
		free(result);
		result = temp;
	}
	return (result);
}

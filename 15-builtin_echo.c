/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15-builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:50:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 12:59:27 by bfleitas         ###   ########.fr       */
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

int ft_isnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


/**
 * Joins the words in the args array into a single string.
 * 
 * @param args The array of words to be joined.
 * @param first_node The pointer to the first node of a linked list.
 * @param i The starting index in the args array.
 * @param word_count The number of words in the args array.
 * @return The resulting string after joining the words.
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
		if ((i < word_count - 1) && (!ft_isnum(args[i])))
		{
			temp = ft_strjoin_g_c(result, " ", first_node);
			result = temp;
		}
		i++;
	}
	return (result);
}


/**
 * Executes the built-in echo command.
 *
 * This function takes an array of arguments, the number of words in the array,
 * and a pointer to a structure `t_ma`. It determines whether a newline character
 * should be added at the end of the output based on the arguments. It then joins
 * the words in the array into a single string, excluding the first word if no
 * newline is required. If a newline is required, it appends it to the result.
 *
 * After that, the function should implement the logic for executing the echo command.
 * This logic is currently missing and needs to be implemented.
 *
 * Finally, if the result string is not NULL, it prints the result to the console
 * using `printf` and returns `EXIT_SUCCESS`. Otherwise, it returns `EXIT_FAILURE`.
 *
 * @param args The array of arguments.
 * @param word_count The number of words in the array.
 * @param ma A pointer to the `t_ma` structure.
 * @return The exit status of the echo command.
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
	// TODO: Implement the logic for executing the echo command
	// ...
	// Return the appropriate exit status
	// ...
	if (result)
	{
		printf("%s", result);
		//free_ntc_prior(first_node, result);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

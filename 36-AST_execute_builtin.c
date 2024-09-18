/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36-AST_execute_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:05 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:27:31 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of words in a given array of strings.
 *
 * This function iterates through an array of strings (arguments) and counts 
 * how many non-null entries it contains.
 *
 * @param args Pointer to the array of strings.
 * @return The total number of strings (words) in the array.
 */
int	count_words(char **args)
{
	char	**temp;
	int		i;

	i = 0;
	temp = args;
	while (temp[i])
		i++;
	return (i);
}

/**
 * @brief Check if a command is a builtin
 *
 * This function checks if the given command is one of the builtin commands
 * supported by the shell.
 *
 * @param simple_cmd The command to check
 * @return int Returns 1 if the command is a builtin, 0 otherwise
 */
int	is_builtin(const char *word)
{
	const char	*builtins[8];
	int			i;

	i = 0;
	i = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i])
	{
		if (ft_strcmp(word, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Executes a built-in shell command based on the input arguments.
 *
 * This function checks the first word in the array to identify which built-in 
 * command is being invoked (e.g., "echo", "cd", "pwd"). It then calls the 
 * corresponding built-in function. If the command is not a recognized built-in, 
 * the function exits with an error.
 *
 * @param words_arr Array of strings representing the command and its arguments.
 * @param ma Pointer to the structure containing environment and memory
 * 			 management.
 */
void	execute_builtin(char **words_arr, t_ma *ma)
{
	int	word_count;

	word_count = count_words(words_arr);
	if (ft_strcmp(words_arr[0], "echo") == 0)
		builtin_echo(words_arr, word_count, ma);
	else if (ft_strcmp(words_arr[0], "cd") == 0)
		builtin_cd(words_arr, ma);
	else if (ft_strcmp(words_arr[0], "pwd") == 0)
		builtin_pwd(words_arr, ma);
	else if (ft_strcmp(words_arr[0], "export") == 0)
		builtin_export(words_arr, ma);
	else if (ft_strcmp(words_arr[0], "unset") == 0)
		builtin_unset(words_arr, ma);
	else if (ft_strcmp(words_arr[0], "env") == 0)
		builtin_env(words_arr, ma);
	else if (ft_strcmp(words_arr[0], "exit") == 0)
		builtin_exit(ma, words_arr);
	else
		exit_or_setexit(1, 1, ma);
}

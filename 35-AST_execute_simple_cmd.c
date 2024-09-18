/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35-AST_execute_simple_cmd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:15 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 05:02:52 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of words in a simple command node.
 *
 * This function traverses the word list in a simple command AST node and 
 * counts the total number of words.
 *
 * @param node Pointer to the simple command AST node.
 * @return The total number of words in the command.
 */
int	node_word_count(t_astnode *node)
{
	int			count;
	t_astnode	*node_word;

	count = 0;
	node_word = node->data.simple_cmd.words;
	while (node_word)
	{
		count++;
		node_word = node_word->data.word.next;
	}
	return (count);
}

/**
 * @brief Creates an array of words from the command's AST node.
 *
 * This function generates an array of words from a simple command node 
 * in the AST. It allocates memory for the array and copies the words from 
 * the node into the array. The function returns the array of words, which 
 * is terminated with a NULL pointer.
 *
 * @param node Pointer to the simple command AST node.
 * @param word_count Pointer to an integer to store the number of words.
 * @param ma Pointer to the structure containing memory management.
 * @return A dynamically allocated array of words, or NULL if allocation fails.
 */
char	**create_words_arr(t_astnode *node, int *word_count, t_ma *ma)
{
	t_astnode	*node_word;
	char		**words_arr;
	int			i;

	i = 0;
	node_word = node->data.simple_cmd.words;
	*word_count = node_word_count(node);
	words_arr = g_c(&(ma->first_node), (*word_count + 1)
			* sizeof(char *))->data;
	if (!words_arr)
	{
		write(2, "malloc error\n", 13);
		return (NULL);
	}
	node_word = node->data.simple_cmd.words;
	while (i < *word_count)
	{
		words_arr[i++] = ft_substr_g_c(node_word->data.word.value, 0,
				ft_strlen(node_word->data.word.value), &(ma->first_node));
		node_word = node_word->data.word.next;
	}
	words_arr[*word_count] = NULL;
	return (words_arr);
}

/**
 * @brief Execute a simple command
 *
 * This function handles the execution of a simple command node. It prepares
 * the arguments, expands wildcards, and executes either a builtin or an
 * external command.
 *
 * @param node Pointer to the simple command node
 * @param ma Pointer to the memory allocation structure
 * @return int Returns the exit status of the executed command
 */
void	execute_simple_cmd(t_astnode *node, t_ma *ma)
{
	t_s_cmd_args	a;

	if (!handle_redirections(node->data.simple_cmd.redirections, ma))
		return ;
	a.words_arr = create_words_arr(node, &(a.word_count), ma);
	if (!a.words_arr)
	{
		exit_or_setexit(1, 0, ma);
		return ;
	}
	execute_words_arr(a.words_arr, ma);
}

/**
 * @brief Execute command with exp_single_arg wildcards
 *
 * This function expands wildcards in the argument array and executes
 * the resulting command, either as a builtin or an external command.
 *
 * @param words_arr The initial argument array
 * @param ma Pointer to the memory allocation structure
 * @return int Returns the exit status of the executed command
 */
void	execute_words_arr(char **words_arr, t_ma *ma)
{
	if (is_builtin(words_arr[0]))
	{
		execute_builtin(words_arr, ma);
		return ;
	}
	if (ma->in_child_p)
	{
		execute_external_cmd(words_arr, &(ma)->env, &(ma)->first_node);
		dup2(ma->saved_stdin, STDIN_FILENO);
		return ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21-AST_execute_simple_cmd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:15 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/11 13:07:17 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int node_word_count(t_astnode *node)
{
    int         count;
    t_astnode   *node_word;
    
    //printf("node_word_count start\n");
    count = 0;
    node_word = node->data.simple_cmd.words;
    while (node_word)
    {
        count++;
        node_word = node_word->data.word.next;
    }
    //printf("node_word_count end\n");
    return (count);
}
/**
 *  * @brief Restore the standard I/O to their original state
 *
 * This function restores the standard input and output to their saved states.
 *
 * @param saved_stdin The saved standard input file descriptor
 * @param saved_stdout The saved standard output file descriptor
*/
static void restore_io(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}

static char **create_words_arr(t_astnode *node, int *word_count, t_ma *ma)
{
    t_astnode   *node_word;
    char        **words_arr;
    int         i;

    i= 0;
    node_word = node->data.simple_cmd.words;
    *word_count = node_word_count(node);
    words_arr = g_c(&(ma->first_node), (*word_count + 1) * sizeof(char *))->data;
    if (!words_arr)
    {
        perror("malloc");
        return NULL;
    }
    node_word = node->data.simple_cmd.words;
    while(i < *word_count)
    {
        words_arr[i++] = ft_substr_g_c(node_word->data.word.value, 0, ft_strlen(node_word->data.word.value), &(ma->first_node));
        node_word = node_word->data.word.next;
    }
    words_arr[*word_count] = NULL;
    //printf("create_words_arr end\n");
    return (words_arr);
}

/**
* @brief Execute a simple command
 *
 * This function handles the execution of a simple command node. It prepares
 * the arguments, checks if it's a builtin command, handles redirections,
 * and either executes the builtin or forks a child process to execute an
 * external command.
 *
 * @param node Pointer to the simple command node
 * @param env Pointer to the environment structure
 * @param first_node Double pointer to the first node in my garbage collector
 * @return int Returns the exit status of the executed command
 */
int execute_simple_cmd(t_astnode *node, t_ma *ma)
{
    t_s_cmd_args   a;

    //printf("execute_simple_cmd start\n");
/*
    t_astnode *tmp = node;
    while (tmp->data.simple_cmd.words)
    {
        printf("node->data.simple_cmd.words->data.word.value = %s\n", tmp->data.simple_cmd.words->data.word.value);
        tmp->data.simple_cmd.words = tmp->data.simple_cmd.words->data.word.next;
    }*/

    a.saved_stdin = dup(STDIN_FILENO);
    a.saved_stdout = dup(STDOUT_FILENO);
    /*if (handle_redirections(node->data.simple_cmd.redirections) != 0)
    {
        restore_io(a.saved_stdin, a.saved_stdout);
        return(1);
    }*/
    a.words_arr = create_words_arr(node, &(a.word_count), ma);
    if (!a.words_arr)
    {
        restore_io(a.saved_stdin, a.saved_stdout);
        return(1);
    }
    //expand_wildcards(a.words_arr);
    if (is_builtin(a.words_arr[0]))
        a.status = execute_builtin(a.words_arr, ma);
    else
        a.status = execute_external_cmd(a.words_arr, ma);
    free_ntc_prior(&(ma->first_node), a.words_arr);
    restore_io(a.saved_stdin, a.saved_stdout);
    //printf("execute_simple_cmd end\n");
    return (a.status);
}





/*
int execute_simple_cmd(t_astnode *node, t_env *env, t_ntc **first_node)
{
    int     words_count;                             // Variable to store the argument count
    int     status;                                // Variable to store the status of the command execution
    char    **args;                                // Pointer to hold the arguments array
    int     saved_stdin = dup(STDIN_FILENO);       // Save the current standard input
    int     saved_stdout = dup(STDOUT_FILENO);     // Save the current standard output

    // Handle any redirections specified in the command
    if (handle_redirections(node->data.simple_cmd.redirections) != 0)
    {
        restore_io(saved_stdin, saved_stdout);     // Restore standard I/O if redirections fail
        return 1;                                  // Return with error status if redirections fail
    }

    // Prepare the arguments for the command execution
    args = create_words_arr(first_node, node, env, &words_count);
    if (!args)
    {
        restore_io(saved_stdin, saved_stdout);     // Restore standard I/O if argument preparation fails
        return 1;                                  // Return with error status if argument preparation fails
    }

    // Expand any wildcards in the arguments
    expand_wildcards(args);

    // Check if the command is a builtin command
    if (is_builtin(args[0]))
    {
        status = execute_builtin(args, env, first_node);  // Execute the builtin command
    }
    else
    {
        status = execute_external_cmd(args, env);  // Execute the external command by forking a child process
    }

    free_args(args);                              // Free the allocated memory for arguments
    restore_io(saved_stdin, saved_stdout);        // Restore the original standard I/O
    return status;                                // Return the status of the command execution
}


 * @brief Restore the standard I/O to their original state
 *
 * This function restores the standard input and output to their saved states.
 *
 * @param saved_stdin The saved standard input file descriptor
 * @param saved_stdout The saved standard output file descriptor

void restore_io(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);  // Restore the saved standard input
    dup2(saved_stdout, STDOUT_FILENO); // Restore the saved standard output
    close(saved_stdin);               // Close the saved standard input descriptor
    close(saved_stdout);              // Close the saved standard output descriptor
}
*/

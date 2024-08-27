 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21-AST_execute_simple_cmd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:15 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/19 10:12:11 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute_exp_single_arg_cmd(char **words_arr, t_ma *ma);

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
void restore_io(int saved_stdin, int saved_stdout)
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
        write(2, "malloc error\n", 13);
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

// /**
// * @brief Execute a simple command
//  *
//  * This function handles the execution of a simple command node. It prepares
//  * the arguments, checks if it's a builtin command, handles redirections,
//  * and either executes the builtin or forks a child process to execute an
//  * external command.
//  *
//  * @param node Pointer to the simple command node
//  * @param env Pointer to the environment structure
//  * @param first_node Double pointer to the first node in my garbage collector
//  * @return int Returns the exit status of the executed command
//  */
// int execute_simple_cmd(t_astnode *node, t_ma *ma)
// {
//     t_s_cmd_args   a;

//     a.saved_stdin = dup(STDIN_FILENO);
//     a.saved_stdout = dup(STDOUT_FILENO);
//     if (!handle_redirections(node->data.simple_cmd.redirections, ma))
//     {
//         restore_io(a.saved_stdin, a.saved_stdout);
//         return(1);
//     }
//     a.words_arr = create_words_arr(node, &(a.word_count), ma);
//     if (!a.words_arr)
//     {
//         restore_io(a.saved_stdin, a.saved_stdout);
//         return(1);
//     }
//     wildcards(a.words_arr);
//     if (is_builtin(a.words_arr[0]))
//     {
//         int exit_code = execute_builtin(a.words_arr, ma);
//         return (exit_code);
//     }
//     else
//         a.status = execute_external_cmd(a.words_arr, &(ma)->env, &(ma)->first_node);
//     free_ntc_prior(&(ma->first_node), a.words_arr);
//     restore_io(a.saved_stdin, a.saved_stdout);
//     return (a.status);
// }

static int  input_is_critical(char **word)
{
    if (ft_strcmp(word[0], "cat") == 0 || ft_strcmp(word[0], "ls") == 0 || ((ft_strcmp(word[0], "echo") == 0) && word[1] == NULL))
        return (1);
    return (0);
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
void execute_simple_cmd(t_astnode *node, t_ma *ma)
{
    t_s_cmd_args    a;
    
    // int status_inp_redir;
    // ft_printf("execute_simple_cmd start\n");
    a.saved_stdin = dup(STDIN_FILENO);
    a.saved_stdout = dup(STDOUT_FILENO);
    a.words_arr = create_words_arr(node, &(a.word_count), ma);
    if(!a.words_arr)
    {
        exit_or_setexit(1, 0, ma);
        return;
    }
    a.i_c = input_is_critical(a.words_arr);
    if(!handle_redirections(node->data.simple_cmd.redirections, &a, ma))
        return;
    execute_exp_single_arg_cmd(a.words_arr, ma);
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
static void execute_exp_single_arg_cmd(char **words_arr, t_ma *ma)
{
    char    **exp_args;
    // int     status;

    exp_args = expand_wildcards_in_args(words_arr, ma);
    if (!exp_args)
    {
        exit_or_setexit(1, 0, ma);
        return;
    }
    if (is_builtin(exp_args[0]))
    {
        // ft_printf("ma->in_child_p: %d\n", ma->in_child_p);// why does this execute or at least land in the exit code if the command is a builtin?
        execute_builtin(exp_args, ma);
        return;
    }
    // ft_printf("ma->in_child_p: %d\n", ma->in_child_p);
    if (ma->in_child_p == 1)
    {
        // write(1, "executing external command\n", 27);
        execute_external_cmd(exp_args, &(ma)->env, &(ma)->first_node);
        return;
    }
}

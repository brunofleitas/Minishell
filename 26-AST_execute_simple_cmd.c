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

static void execute_words_arr(char **words_arr, t_ma *ma);

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

static int  input_is_critical(t_astnode *first_word_node)
{
    char        *command;
    t_astnode   *next_word;

    if (first_word_node == NULL)
        return (0);
    command = first_word_node->data.word.value;
    next_word = first_word_node->data.word.next;
    if (ft_strcmp(command, "cat") == 0 || ft_strcmp(command, "ls") == 0 || ((ft_strcmp(command, "echo") == 0) && next_word == NULL))
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
    a.s_inredir = 0;
    a.i_c = input_is_critical(node->data.simple_cmd.words);
    if(!handle_redirections(node->data.simple_cmd.redirections, &a, ma))
        return;
    a.words_arr = create_words_arr(node, &(a.word_count), ma);
    if(!a.words_arr)
    {
        exit_or_setexit(1, 0, ma);
        return;
    }
    // if (a.i_c && !a.s_inredir)
    //     verif_input_available)
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
static void execute_words_arr(char **words_arr, t_ma *ma)
{
    // int     status;

    if (is_builtin(words_arr[0]))
    {
        // ft_printf("ma->in_child_p: %d\n", ma->in_child_p);// why does this execute or at least land in the exit code if the command is a builtin?
        execute_builtin(words_arr, ma);
        return;
    }
    // ft_printf("ma->in_child_p: %d\n", ma->in_child_p);
    if (ma->in_child_p == 1)
    {
        // write(1, "executing external command\n", 27);
        execute_external_cmd(words_arr, &(ma)->env, &(ma)->first_node);
        return;
    }
}

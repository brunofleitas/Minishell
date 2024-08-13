/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18-redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:52:15 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/26 02:59:05 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
  Function to redirect input from a file.
  Opens the file for reading.
  Redirects the standard input to the file.
  If an error occurs during file operations, an error message is printed.
*/
void redirect_input(const char *file_name)
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file for input redirection");
        return;
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("Error redirecting input from file");
    }
    close(fd);
}


/*
  Function to redirect output to a file.
  Opens the file with truncation mode, creating it if it doesn't exist.
  Writes the output string to the file.
  If an error occurs during file operations, an error message is printed.
*/
void redirect_output(const char *output, const char *file_name)
{
    int fd;

    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error opening file for output redirection");
        return;
    }
    if (write(fd, output, strlen(output)) == -1)
    {
        perror("Error writing to file during output redirection");
    }
    close(fd);
}


/*
  Function to append output to a file.
  Opens the file in append mode, creating it if it doesn't exist.
  Appends the output string to the file.
  If an error occurs during file operations, an error message is printed.
*/
void redirect_output_append(const char *output, const char *file_name)
{
    int fd;

    fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("Error opening file for append output redirection");
        return;
    }
    if (write(fd, output, strlen(output)) == -1)
    {
        perror("Error writing to file during append output redirection");
    }
    close(fd);
}


/*
  Function to handle redirections.
  Iterates over the list of redirection nodes and applies the necessary redirections.
  Depending on the type of redirection, calls the appropriate function.
*/
void handle_redirections(t_astnode *redir_node, const char *output)
{
    while (redir_node != NULL)
    {
        if (redir_node->data.redirection.type == TOKEN_REDIR_OUT)
        {
            redirect_output(output, redir_node->data.redirection.file);
        }
        else if (redir_node->data.redirection.type == TOKEN_REDIR_APPEND)
        {
            redirect_output_append(output, redir_node->data.redirection.file);
        }
        else if (redir_node->data.redirection.type == TOKEN_REDIR_IN)
        {
            redirect_input(redir_node->data.redirection.file);
        }
        redir_node = redir_node->data.redirection.next;
    }
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18-redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:52:15 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 18:00:20 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Redirects the input from a file to the standard input.
 * 
 * @param file_name The name of the file to redirect input from.
 */
static int redirect_input(const char *file_name)
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        write(2," No such file or directory", 27);
        return(0);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        write(2, "Error redirecting input from file", 34);
        close(fd);
        return(0);
    }
    close(fd);
    return(1);
}


/**
 * Redirects the output of a file descriptor to a specified file.
 *
 * @param file_name The name of the file to redirect the output to.
 * @param fd_num The file descriptor number to redirect.
 */
static int redirect_output(const char *file_name, int fd_num)
{
    int fd; 
    
    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        write(2, " Permission denied", 18);
        return(0);  
    }
    if (dup2(fd, fd_num) == -1)
    {
        write(2, "Error redirecting output to file", 33);
        close(fd);
        return(0);
    }
    close(fd);
    return(1);
}


/**
 * Redirects the output of a file descriptor to a file in append mode.
 *
 * @param file_name The name of the file to redirect the output to.
 * @param fd_num The file descriptor number to redirect the output from.
 */
static int redirect_output_append(const char *file_name, int fd_num)
{
    int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        write(2, "Error opening file for append output redirection", 47);
        return(0);
    }
    if (dup2(fd, fd_num) == -1)
    {
        write(2, "Error redirecting output to file for append", 43);
        close(fd);
        return(0);
    }
    close(fd);
    return(1);
}


/**
 * Generates a unique filename for a temporary file.
 * The filename is generated based on a base string and a counter.
 * The counter is incremented each time this function is called.
 *
 * @param ma The main structure containing program data.
 * @return A dynamically allocated string representing the unique filename,
 *         or NULL if an error occurred.
 */
static char *give_tmp_name(t_ma *ma)
{
    char *temp_file_name;
    const char *base;
    char *counter_str;

    base = "/tmp/heredoc_";
    counter_str = ft_itoa_g_c(ma->tmp_file_counter++, &(ma->first_node));
    if (!counter_str)
    {
        write(2, "Error allocating memory for counter string", 42);
        return (NULL);
    }
    temp_file_name = ft_strjoin_g_c(base, counter_str, &(ma->first_node));
    if (!temp_file_name)
    {
        write(2, "Error allocating memory for temporary file path", 48);
        return (NULL);
    }
    return (temp_file_name);
}

/**
 * Writes input lines to a temporary file until a delimiter is encountered.
 *
 * @param fd              The file descriptor to write to.
 * @param delimiter       The delimiter string that indicates the end of input.
 * @param temp_file_name  The name of the temporary file.
 * @return                Returns 0 on success, -1 on failure.
 */
static int write_to_tmp_file(int fd, const char *delimiter)
{
    char *line;

    while (1)
    {
        line = readline(" heredoc>");
        if (!line)
        {
            write(2, "Error reading input for heredoc", 32);
            return (0);
        }
        if (ft_strcmp(line, delimiter) == 0)
            break;
        if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
        {
            write(2, "Error writing to temporary file", 32);
            return (0);
        }
    }
    return (1);
}

/**
 * Creates a temporary file with the given name and writes the specified delimiter to it.
 * 
 * @param temp_file_name The name of the temporary file to create.
 * @param delimiter The delimiter to write to the temporary file.
 * @return 0 if the temporary file is created and written successfully, -1 otherwise.
 */
static int create_tmp_file(const char *temp_file_name, const char *delimiter)
{
    int fd;

    fd = open(temp_file_name, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd == -1)
    {
        write(2, "Error creating temporary file for heredoc", 41);
        return (0);
    }

    if (!write_to_tmp_file(fd, delimiter))
    {
        close(fd);
        unlink(temp_file_name);
        return (0);
    }
    close(fd);
    return (1);
}


/**
 * Handles the heredoc functionality by creating a temporary file with the given delimiter.
 * The temporary file is used to redirect input for the current command.
 * 
 * @param delimiter The delimiter used to mark the end of the heredoc input.
 * @param ma The main structure containing the necessary information for the shell.
 */
static int handle_heredoc(const char *delimiter, t_ma *ma)
{
    char *temp_file_name;

    temp_file_name = give_tmp_name(ma);
    if (!temp_file_name)
        return(0);
    if (!create_tmp_file(temp_file_name, delimiter))
        return (0);
    redirect_input(temp_file_name);
    if (unlink(temp_file_name) == -1)
    {
        write(2, "Error unlinking temporary file", 30);
        return (0);
    }
    return (1);
}

/**
 * Handles the redirections specified in the given AST node.
 * 
 * @param redir_node The AST node containing the redirections.
 * @param ma The main data structure of the program.
 */
int handle_redirections(t_astnode *redir_node, t_ma *ma)
{
    // int fd_num;

    while (redir_node != NULL)
    {
        if (redir_node->data.redirection.type == TOKEN_REDIR_OUT 
            && !redirect_output(redir_node->data.redirection.file, 1))
            return (0);
        else if (redir_node->data.redirection.type == TOKEN_REDIR_APPEND 
            && !redirect_output_append(redir_node->data.redirection.file, 1))
            return (0);
        else if (redir_node->data.redirection.type == TOKEN_REDIR_IN 
            && !redirect_input(redir_node->data.redirection.file))
            return (0);
        else if (redir_node->data.redirection.type == TOKEN_HEREDOC 
            && !handle_heredoc(redir_node->data.redirection.file, ma))
            return (0);
        redir_node = redir_node->data.redirection.next;
    }
    return (1);
}
/* 
block removed at the beginning of the function because it was not used
if (redir_node->data.redirection.type == TOKEN_REDIR_OUT_NUM
            || redir_node->data.redirection.type == TOKEN_REDIR_APPEND_NUM)
            fd_num = ma->c_tkn[0]->value[0] - '0';
        else
            fd_num = STDOUT_FILENO;
        if (fd_num == ('&' - '0'))
        {
            printf("handle_12_redir start\n");
            handle_12_redir(redir_node);
            printf("handle_12_redir end\n");
        }
        else  */
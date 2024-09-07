char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>

char	*gnl(int fd);
#include <unistd.h>
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23-redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:52:15 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/27 17:04:27 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * Redirects the input from a file to the standard input.
 * 
 * @param file_name The name of the file to redirect input from.
 */
static int redirect_input(char *file_name, t_s_cmd_args *a, t_ma *ma)
{
    int fd;

        fd = open(file_name, O_RDONLY);
        if (fd == -1)
        {
            write(2, ma->program, ma->l_program); //doesn't work need to find out why
            // write(2, "minishell: ", 11);
            write(2, file_name, ft_strlen(file_name));
            write(2, ": No such file or directory\n", 28);
            return(0);
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            close(fd);
            return(0);
        }
        close(fd);
        a->s_inredir += 1;
        return(1);
}


/**
 * Redirects the output of a file descriptor to a specified file.
 *
 * @param file_name The name of the file to redirect the output to.
 * @param fd_num The file descriptor number to redirect.
 */
static int redirect_output(char *file_name, int fd_num, t_ma *ma)
{
    int fd; 

        fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
        if (fd == -1)
        {
            write(2, ma->program, ma->l_program); //doesn't work need to find out why
            // write(2, "minishell: ", 11);
            write(2, file_name, ft_strlen(file_name));
            write(2, ": Permission denied\n", 20);
            return(0);
        }
        if (dup2(fd, fd_num) == -1)
        {
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
static int redirect_output_append(char *file_name, int fd_num, t_ma *ma)
{
    int fd;

        fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
        if (fd == -1)
        {
            write(2, ma->program, ma->l_program); //doesn't work need to find out why
            // write(2, "minishell: ", 11);
            write(2, file_name, ft_strlen(file_name));
            write(2, ": Permission denied\n", 21);
            return(0);
        }
        if (dup2(fd, fd_num) == -1)
        {
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
        // perror(" ");
        return (NULL);
    }
    temp_file_name = ft_strjoin_g_c(base, counter_str, &(ma->first_node));
    if (!temp_file_name)
    {
        // perror(" ");
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
static int write_to_tmp_file(int fd, const char *delimiter, t_ma *ma)
{
    char *line;
    int i;
    int len;
    int var_len;
    char *temp;
    char *env_value;

//write (1, "heredoc> ", 9);
        line = gnl(0);
    while (ft_strcmp(line, delimiter) != 0)
    {
        //line = !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : readline(" heredoc>");
        
        if (!line)
        {
            // perror(" ");
            return (0);
        }
        if (ft_strcmp(line, delimiter) == 0)
            break;
        len = ft_strlen(line);
        i = 0;
        while (i < len)
        {
            if (line[i] == '$' && line[i + 1] == '?')
            {
                write(fd, ft_itoa_g_c(ma->last_exit_status, &(ma->first_node)), ft_strlen(ft_itoa_g_c(ma->last_exit_status, &(ma->first_node))));
                i += 2;
            }
            else if (line[i] == '$' && ((ft_isalnum(line[i + 1])) || line[i + 1] == '_')) 
            {
                var_len = 0;
                while (line[i + var_len + 1] && ((ft_isalnum(line[i + var_len + 1]) || line[i + var_len + 1] == '_')))
                    var_len++;
                temp = ft_substr_g_c(line + i + 1, 0, var_len, &(ma->first_node)); // Corrected line
                env_value = get_env(temp, ma->env->var);
                if (env_value)
                {
                    write(fd, env_value, ft_strlen(env_value));
                }
                i += var_len + 1;
            }
            else
            {
                write(fd, &line[i], 1); // Corrected line
                i++;
            }
        }
        write(fd, "\n", 1);
        //write (1, "heredoc> ", 9);
        line = gnl(0);
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
static int create_tmp_file(const char *temp_file_name, const char *delimiter, t_ma *ma)
{
    int fd;

    fd = open(temp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
    {
        // perror(" ");
        return (0);
    }
    if (!write_to_tmp_file(fd, delimiter, ma))
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
static int handle_heredoc(const char *delimiter, t_s_cmd_args *a, t_ma *ma)
{
    char *temp_file_name;

    temp_file_name = give_tmp_name(ma);
    if (!temp_file_name)
        return(0);
    if (!create_tmp_file(temp_file_name, delimiter, ma))
        return (0);
    redirect_input(temp_file_name, a, ma);
    if (unlink(temp_file_name) == -1)
        return (0);
    return (1);
}

/* #include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

static int handle_heredoc(const char *delimiter, t_s_cmd_args *a, t_ma *ma)
{
    char *temp_file_name;
    pid_t pid;
    int status;

    // Verificamos si es necesario el fork
    if (!isatty(0))
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            return 0;
        }
        else if (pid == 0) // Proceso hijo
        {
            // Lógica de manejo de heredoc en el proceso hijo
            temp_file_name = give_tmp_name(ma);
            if (!temp_file_name)
                exit(EXIT_FAILURE);  // Salimos si fallamos en dar un nombre al archivo temporal
            if (!create_tmp_file(temp_file_name, delimiter, ma))
                exit(EXIT_FAILURE);  // Salimos si fallamos en crear el archivo temporal
            if (!redirect_input(temp_file_name, a, ma))
                exit(EXIT_FAILURE);  // Salimos si falla la redirección
            if (unlink(temp_file_name) == -1) // Eliminamos el archivo temporal
                exit(EXIT_FAILURE);  // Salimos si no podemos eliminar el archivo temporal
            exit(EXIT_SUCCESS);  // El proceso hijo termina con éxito
        }
        else // Proceso padre
        {
            // El proceso padre espera que el hijo termine
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
                return 1; // Éxito en el proceso hijo
            else
                return 0; // Fallo en el proceso hijo
        }
    }
    else
    {
        // Si isatty(0) es verdadero, ejecutamos la lógica heredoc en el proceso principal
        temp_file_name = give_tmp_name(ma);
        if (!temp_file_name)
            return 0;
        if (!create_tmp_file(temp_file_name, delimiter, ma))
            return 0;
        if (!redirect_input(temp_file_name, a, ma))
            return 0;
        if (unlink(temp_file_name) == -1)
            return 0;
        return 1;
    }
} */


/**
 * Exits the shell if the given error code is non-zero.
 * 
 * @param e The error code to check. Set to 0 if no error occurred, non-zero an error occured.
 * @param e_throw_err If true, an error message is printed.
 * @param ma The main structure containing the necessary information for the shell.
 */
void exit_or_setexit(int e, int e_throw_err, t_ma *ma)
{
    (void)e_throw_err;
    if (!e)
    {
        if (ma->in_child_p)
            exit(EXIT_SUCCESS);
        else
             ma->last_exit_status = e;
    }
    else
    {
        if (e_throw_err)
            perror(" ");
        if (ma->in_child_p)
            exit(EXIT_FAILURE);
        else
            ma->last_exit_status = e;
    }
}

/**
 * Handles the redirections specified in the given AST node.
 * 
 * @param redir_node The AST node containing the redirections.
 * @param ma The main data structure of the program.
 */
int handle_redirections(t_astnode *redir_node, t_s_cmd_args *a, t_ma *ma)
{
    while (redir_node != NULL)
    {
        if ((redir_node->data.redirection.type == TOKEN_REDIR_OUT 
            && !redirect_output(redir_node->data.redirection.file, 1, ma)) ||
            (redir_node->data.redirection.type == TOKEN_REDIR_APPEND 
            && !redirect_output_append(redir_node->data.redirection.file, 1, ma))||
            (redir_node->data.redirection.type == TOKEN_REDIR_IN 
            && !redirect_input(redir_node->data.redirection.file, a, ma)) ||
            (redir_node->data.redirection.type == TOKEN_HEREDOC 
            && !handle_heredoc(redir_node->data.redirection.file, a, ma)))
            {
                if ((redir_node->data.redirection.type == TOKEN_REDIR_IN  || 
                redir_node->data.redirection.type == TOKEN_HEREDOC) && !a->i_c)
                {
                    restore_io(ma);
                    exit_or_setexit(1,0, ma);
                    return (0);
                }
                else
                {
                    restore_io(ma);
                    exit_or_setexit(1, 0, ma);
                    return (0);
                }
            }
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

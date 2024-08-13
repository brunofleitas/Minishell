#include "minishell.h"


/**
 * Redirects the input from a file to the standard input.
 * 
 * @param file_name The name of the file to redirect input from.
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


/**
 * Redirects the output of a file descriptor to a specified file.
 *
 * @param file_name The name of the file to redirect the output to.
 * @param fd_num The file descriptor number to redirect.
 */
void redirect_output(const char *file_name, int fd_num)
{
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error opening file for output redirection");
        return;
    }
    if (dup2(fd, fd_num) == -1)
        perror("Error redirecting output to file");
    close(fd);
}


/**
 * Redirects the output of a file descriptor to a file in append mode.
 *
 * @param file_name The name of the file to redirect the output to.
 * @param fd_num The file descriptor number to redirect the output from.
 */
void redirect_output_append(const char *file_name, int fd_num)
{
    int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("Error opening file for append output redirection");
        return;
    }
    if (dup2(fd, fd_num) == -1)
        perror("Error redirecting output to file for append");
    close(fd);
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
char *generate_unique_filename(t_ma *ma)
{
    char *temp_file_name;
    const char *base;
    char *counter_str;

    base = "/tmp/heredoc_";
    counter_str = ft_itoa(ma->tmp_file_counter++);
    if (!counter_str)
    {
        perror("Error allocating memory for counter string");
        return NULL;
    }
    temp_file_name = ft_strjoin(base, counter_str);
    free(counter_str);
    if (!temp_file_name)
    {
        perror("Error allocating memory for temporary file path");
        return NULL;
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
static int write_to_tmp_file(int fd, const char *delimiter, const char *temp_file_name)
{
    char *line;

    while (1)
    {
        line = readline(" >");
        if (!line)
        {
            perror("Error reading input for heredoc");
            return -1;
        }
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        if (write(fd, line, strlen(line)) == -1 || write(fd, "\n", 1) == -1)
        {
            perror("Error writing to temporary file");
            free(line);
            return -1;
        }
        free(line);
    }
    return (0);
}

/**
 * Creates a temporary file with the given name and writes the specified delimiter to it.
 * 
 * @param temp_file_name The name of the temporary file to create.
 * @param delimiter The delimiter to write to the temporary file.
 * @return 0 if the temporary file is created and written successfully, -1 otherwise.
 */
int create_tmp_file(const char *temp_file_name, const char *delimiter)
{
    int fd;

    fd = open(temp_file_name, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd == -1)
    {
        perror("Error creating temporary file for heredoc");
        return -1;
    }

    if (write_to_tmp_file(fd, delimiter, temp_file_name) == -1)
    {
        close(fd);
        unlink(temp_file_name);
        return -1;
    }

    close(fd);
    return 0;
}


/**
 * Handles the heredoc functionality by creating a temporary file with the given delimiter.
 * The temporary file is used to redirect input for the current command.
 * 
 * @param delimiter The delimiter used to mark the end of the heredoc input.
 * @param ma The main structure containing the necessary information for the shell.
 */
void handle_heredoc(const char *delimiter, t_ma *ma)
{
    char *temp_file_name;

    temp_file_name = give_tmp_name(ma);
    if (!temp_file_name)
        return;

    if (create_tmp_file(temp_file_name, delimiter) == -1)
    {
        free(temp_file_name);
        return;
    }
    redirect_input(temp_file_name);
    if (unlink(temp_file_name) == -1)
        perror("Error unlinking temporary file");

    free(temp_file_name);
}



/**
 * Handles the redirections specified in the given AST node.
 * 
 * @param redir_node The AST node containing the redirections.
 * @param ma The main data structure of the program.
 */
void handle_redirections(t_astnode *redir_node, t_ma *ma)
{
    while (redir_node != NULL)
    {
        int fd_num = redir_node->data.redirection.fd_num;
        if (redir_node->data.redirection.type == TOKEN_REDIR_OUT)
            redirect_output(redir_node->data.redirection.file, fd_num);
        else if (redir_node->data.redirection.type == TOKEN_REDIR_APPEND)
            redirect_output_append(redir_node->data.redirection.file, fd_num);
        else if (redir_node->data.redirection.type == TOKEN_REDIR_IN)
            redirect_input(redir_node->data.redirection.file);
        else if (redir_node->data.redirection.type == TOKEN_HEREDOC)
            handle_heredoc(redir_node->data.redirection.file, ma);
        redir_node = redir_node->data.redirection.next;
    }
}
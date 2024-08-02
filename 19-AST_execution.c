#include "minishell.h"

/**
 @brief Main execution function for the AST

 This function serves as the entry point for executing the Abstract Syntax Tree (AST).
 It determines the type of the node and calls the appropriate execution function.

 @param node Pointer to the current AST node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the executed command
*/
int execute_ast(t_astnode *node, t_env *env)
{
    if (!node)
        return (0);
    if (node->type == NODE_CMD_LINE)
        return (execute_cmd_line(node, env));
    else if (node->type == NODE_PIPELINE)
        return (execute_pipeline(node, env));
    else if (node->type == NODE_SIMPLE_CMD)
        return (execute_simple_cmd(node, env));
    else
    {
        ft_putstr_fd("Error: Unknown node type\n", STDERR_FILENO);// just an Idea I got if we want a file where we store all the errors
        return (1);
    }
}

/**
 @brief Execute a command line node

 This function handles the execution of a command line node, which can contain
 multiple commands connected by AND (&&) or OR (||) operators.

 @param node Pointer to the command line node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the last executed command
 */
int execute_cmd_line(t_astnode *node, t_env *env)
{
    int left_result;
    
    left_result = execute_ast(node->data.cmd_line.left, env);
    if (node->data.cmd_line.operator == TOKEN_AND)
    {
        if (left_result == 0)
            return (execute_ast(node->data.cmd_line.right, env));
        return left_result;
    }
    else if (node->data.cmd_line.operator == TOKEN_OR)
    {
        if (left_result != 0)
            return (execute_ast(node->data.cmd_line.right, env));
        return left_result;
    }
    
    return (left_result);
}

/**
 @brief Execute a pipeline of commands

 This function handles the execution of a pipeline node, which contains
 multiple commands connected by pipes (|). It creates the necessary pipes
 and forks child processes to execute each command in the pipeline.

 @param node Pointer to the pipeline node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the last command in the pipeline
 */
int execute_pipeline(t_astnode *node, t_env *env)
{
    int i = 0;
    int pipe_fds[2];
    int in_fd = STDIN_FILENO;
    pid_t pid;
    int status;
    int last_pid;

    while (i < node->data.pipeline.cmd_count)
    {
        if (i < node->data.pipeline.cmd_count - 1)
        {
            if (pipe(pipe_fds) == -1)
            {
                perror("pipe");
                exit(1);
            }
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            if (in_fd != STDIN_FILENO)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            if (i < node->data.pipeline.cmd_count - 1)
            {
                dup2(pipe_fds[1], STDOUT_FILENO);
                close(pipe_fds[0]);
                close(pipe_fds[1]);
            }

            exit(execute_ast(node->data.pipeline.cmds[i], env));
        }
        else
        {
            // Parent process
            if (in_fd != STDIN_FILENO)
                close(in_fd);

            if (i < node->data.pipeline.cmd_count - 1)
            {
                close(pipe_fds[1]);
                in_fd = pipe_fds[0];
            }

            last_pid = pid;
        }
        i++;
    }

    // Wait for the last command in the pipeline
    waitpid(last_pid, &status, 0);
    return WEXITSTATUS(status);
}

/**
 @brief Execute a simple command

 This function handles the execution of a simple command node. It prepares
 the arguments, checks if it's a builtin command, handles redirections,
 and either executes the builtin or forks a child process to execute an
 external command.

 @param node Pointer to the simple command node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the executed command
 */
int execute_simple_cmd(t_astnode *node, t_env *env)
{
    char **args;
    int arg_count = 0;
    t_astnode *word_node = node->data.simple_cmd.words;
    pid_t pid;
    int status;

    // Count arguments
    while (word_node)
    {
        arg_count++;
        word_node = word_node->data.word.next;
    }

    // Allocate args array
    args = malloc((arg_count + 1) * sizeof(char *));
    if (!args)
    {
        perror("malloc");
        return 1;
    }

    // Fill args array
    word_node = node->data.simple_cmd.words;
    int i = 0;
    while (i < arg_count)
    {
        args[i] = expand_env_vars(word_node->data.word.value, env);
        word_node = word_node->data.word.next;
        i++;
    }
    args[arg_count] = NULL;

    // Expand wildcards
    expand_wildcards(args);

    // Handle builtin commands
    if (is_builtin(args[0]))
        return execute_builtin(args, env);

    // Handle redirections
    if (handle_redirections(node->data.simple_cmd.redirections) != 0)
    {
        free_args(args);
        return 1;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free_args(args);
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        execve(args[0], args, env->var);
        perror("execve");
        exit(1);
    }
    else
    {
        // Parent process
        waitpid(pid, &status, 0);
        free_args(args);
        return WEXITSTATUS(status);
    }
}

/**
 @brief Free the argument array

 This function frees the memory allocated for the argument array.

 @param args The argument array to be freed
 */
void free_args(char **args)
{
    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}
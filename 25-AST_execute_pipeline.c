/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25-AST_execute_pipeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:23 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/09 23:13:00 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void setup_pipe(int pipe_fds[2])
{
    //printf("setup_pipe start\n");
    if (pipe(pipe_fds) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    //printf("setup_pipe end\n");
}

static void child_process(t_pip_args *a, t_astnode *simple_cmd, t_ma *ma)
{
    // write(1, "Enter fork lvl: ", 16);
    // ft_putnbr_fd(ma->in_child_p, 1);
    // write(1, "\n", 1);
    // printf("child_process start\n");
    if (a->input_fd != STDIN_FILENO)
    {
        dup2(a->input_fd, STDIN_FILENO);
        close(a->input_fd);
    }
    if (!a->last_cmd)
    {
        dup2(a->pipe_fds[1], STDOUT_FILENO);
        close(a->pipe_fds[0]);
        close(a->pipe_fds[1]);
    }
    ma->in_child_p++;
    ma->and_or = 0;
    //printf("child_process end\n");
    execute_ast(simple_cmd, ma); //what is this function?
}

static void parent_process(t_pip_args *a)
{
    //printf("parent_process start\n");
    if (a->input_fd != STDIN_FILENO)
        close(a->input_fd);
    if (!(a->last_cmd))
    {
        close(a->pipe_fds[1]);
        a->input_fd = a->pipe_fds[0];
    }
    //printf("parent_process end\n");
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
void execute_pipeline(t_astnode *node, t_ma *ma)
{
    t_pip_args  a;
    int         i;
    // int         original_stdout;
    
    //printf("execute_pipeline start\n");
    i = 0;
    a.input_fd = STDIN_FILENO;
    if (node->data.pipeline.cmd_count == 1 && 
    (node->data.pipeline.cmds[0]->data.simple_cmd.words && (node->data.pipeline.cmds[0]->data.simple_cmd.words[0].data.word.type == TOKEN_BUILTIN)))//added here a sef\g fault check
    {
        execute_ast(node->data.pipeline.cmds[0], ma);
        return;
        // close(original_stdout);
    }
    a.pid_arr = g_c(&(ma->first_node), sizeof(pid_t) * (node->data.pipeline.cmd_count))->data;
    while (i < node->data.pipeline.cmd_count)
    {
        a.last_cmd = (i == node->data.pipeline.cmd_count - 1);
        if (!a.last_cmd)
            setup_pipe(a.pipe_fds);
        a.pid_arr[i] = fork();
        if (a.pid_arr[i] == -1)
            exit_or_setexit(1, 1, ma);
        if (a.pid_arr[i] == 0)
            child_process(&a, node->data.pipeline.cmds[i], ma);
        else
            parent_process(&a);
        i++;
    }
    // dup2(original_stdout, STDOUT_FILENO);
    // close(original_stdout);
    i = 0;
    while (i < node->data.pipeline.cmd_count)
    {
        waitpid(a.pid_arr[i], &(a.status), 0);
        if (i == node->data.pipeline.cmd_count - 1)
            a.last_status = a.status;
        i++;
    }
    if (WIFEXITED(a.last_status))
        exit_or_setexit(WEXITSTATUS(a.last_status), 0, ma);
    else if (WIFSIGNALED(a.last_status))
        exit_or_setexit(WTERMSIG(a.last_status), 0, ma);
    return;
    //printf("execute_pipeline end\n");
    // return (WEXITSTATUS(a.last_status));
}
// This implementation of simple command execution is incomplete. It does not handle the case where for exemple we have export PATH=new/path/added | env and then execute env again as it will only have been updated in the child process.





// #include "minishell.h"

// /**
//  * @brief Sets up a pipe for inter-process communication.
//  * 
//  * This function creates a pipe using the `pipe()` system call and checks 
//  * if the pipe was successfully created. The pipe file descriptors are stored 
//  * in the array `pipe_fds`.
//  * 
//  * @param pipe_fds An array of two integers where the pipe file descriptors are stored.
//  */
// static void setup_pipe(int pipe_fds[2])
// {
//     if (pipe(pipe_fds) == -1)
//     {
//         perror("pipe");
//         exit(1);
//     }
// }

// /**
//  * @brief Forks a new process.
//  * 
//  * This function creates a new process by calling `fork()` and checks if the 
//  * fork was successful. It returns the process ID of the child process.
//  * 
//  * @return pid_t The process ID of the child process, or -1 if fork failed.
//  */
// pid_t fork_process()
// {
//     pid_t pid;
    
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         exit(1);
//     }
//     return (pid);
// }

// /**
//  * @brief Executes the command in the child process.
//  * 
//  * This function sets up the file descriptors for the child process based on 
//  * whether it's the first or last command in the pipeline. It then calls 
//  * `execute_ast()` to execute the command.
//  * 
//  * @param a Structure containing the pipeline arguments.
//  * @param simple_cmd The AST node representing the simple command to execute.
//  * @param ma Pointer to the main minishell structure (environment and other data).
//  */
// static void child_process(t_pip_args *a, t_astnode *simple_cmd, t_ma *ma)
// {
//     if (a->input_fd != STDIN_FILENO)
//     {
//         dup2(a->input_fd, STDIN_FILENO); // Redirect input to the read end of the previous pipe
//         close(a->input_fd); // Close the original input file descriptor
//     }
//     if (!a->last_cmd)
//     {
//         dup2(a->pipe_fds[1], STDOUT_FILENO); // Redirect output to the write end of the current pipe
//         close(a->pipe_fds[0]); // Close the read end of the pipe in the child process
//         close(a->pipe_fds[1]); // Close the original write end of the pipe
//     }
//     exit(execute_ast(simple_cmd, ma)); // Execute the command and exit the child process
// }

// /**
//  * @brief Manages the parent process after forking a child.
//  * 
//  * This function closes the unnecessary file descriptors in the parent process 
//  * and prepares the input for the next command in the pipeline.
//  * 
//  * @param a Structure containing the pipeline arguments.
//  */
// static void parent_process(t_pip_args *a)
// {
//     if (a->input_fd != STDIN_FILENO)
//         close(a->input_fd); // Close the previous input file descriptor

//     if (!(a->last_cmd))
//     {
//         close(a->pipe_fds[1]); // Close the write end of the pipe
//         a->input_fd = a->pipe_fds[0]; // Set the input for the next command to the read end of the pipe
//     }
//     a->last_status = a->pid; // Store the PID of the last forked child process
// }

// /**
//  * @brief Execute a pipeline of commands.
//  * 
//  * This function handles the execution of a pipeline node, which contains
//  * multiple commands connected by pipes (|). It creates the necessary pipes
//  * and forks child processes to execute each command in the pipeline.
//  * 
//  * It only waits for the last process in the pipeline to finish. However, 
//  * to accurately mimic the shell behavior, it should wait for all processes.
//  * 
//  * @param node Pointer to the pipeline node.
//  * @param ma Pointer to the main minishell structure (environment and other data).
//  * @return int Returns the exit status of the last command in the pipeline.
//  */
// int execute_pipeline(t_astnode *node, t_ma *ma)
// {
//     t_pip_args  a;
//     int         i;

//     i = 0;
//     a.input_fd = STDIN_FILENO; // Start with the standard input as the input FD

//     if (node->data.pipeline.cmd_count == 1)
//         return (execute_ast(node->data.pipeline.cmds[0], ma));
//     else
//     {
//         while (i < node->data.pipeline.cmd_count)
//         {
//             a.last_cmd = (i == node->data.pipeline.cmd_count - 1); // Check if it's the last command in the pipeline
//             if (!a.last_cmd)
//                 setup_pipe(a.pipe_fds); // Setup a pipe for communication between processes

//             a.pid = fork_process(); // Fork a new process

//             if (a.pid == 0)
//                 child_process(&a, node->data.pipeline.cmds[i], ma); // In the child process, execute the command
//             else
//                 parent_process(&a); // In the parent process, manage the pipe FDs

//             i++;
//         }

//      

//         return (0); // Return success, as we are assuming execute_ast handles command failures
//     }
// }

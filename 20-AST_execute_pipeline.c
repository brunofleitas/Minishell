/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20-AST_execute_pipeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:23 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/12 00:10:15 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void setup_pipe(int pipe_fds[2])
{
    //printf("setup_pipe start\n");
    if (pipe(pipe_fds) == -1)
    {
        perror("pipe");
        exit(1);
    }
    //printf("setup_pipe end\n");
}
pid_t    fork_process()
{
    pid_t pid;
    
    //printf("fork_process start\n");
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    //printf("fork_process end\n");
    return (pid);
}

static void child_process(t_pip_args *a, t_astnode *simple_cmd, t_ma *ma)
{
    //printf("child_process start\n");
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
    //printf("child_process end\n");
    exit(execute_ast(simple_cmd, ma)); //what is this function?
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
    a->last_pid = a->pid;
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
int execute_pipeline(t_astnode *node, t_ma *ma)
{
    t_pip_args  a;
    int         i;
    
    //printf("execute_pipeline start\n");
    i = 0;
    a.input_fd = STDIN_FILENO;
    if (node->data.pipeline.cmd_count == 1)
        return (execute_ast(node->data.pipeline.cmds[0], ma));
    else
    {
        while (i < node->data.pipeline.cmd_count)
        {
            a.last_cmd = (i == node->data.pipeline.cmd_count - 1);
            if (!node->data.pipeline.cmd_count - 1)
                setup_pipe(a.pipe_fds);
            a.pid = fork_process();
            if (a.pid == 0)
                child_process(&a, node->data.pipeline.cmds[i], ma);
            else
                parent_process(&a);
            i++;
        }
        waitpid(a.last_pid, &(a.status), 0);
    }
    //printf("execute_pipeline end\n");
    return (WEXITSTATUS(a.status));
}
// This implementation of simple command execution is incomplete. It does not handle the case where for exemple we have export PATH=new/path/added | env and then execute env again as it will only have been updated in the child process.
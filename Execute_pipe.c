/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:57:37 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/31 23:57:52 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_pipeline(t_astnode *node)
{
    int     pipefd[2];
    pid_t   pid;

    if (!node)
        return 0;
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid = 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        if (/*there is a builtin command*/)
            execute_builtin(node);
        else
            execute_external_command(node);
        close(pipefd[1]);
        exit(EXIT_SUCCESS);//check if it is the right exit
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);

        if (node->data.pipeline.cmds)
        execute_pipeline(node->data.pipeline.cmds++);
        close(pipefd[0]);
        waitpid(pid, NULL, 0);`
        exit(EXIT_SUCCESS);
    }
}


int execute_pipe(t_astnode *node)
{
    int     pipefd[2];
    pid_t   pid;

    if (node->data.pipeline.cmd_count == 1)
    {
        execute_simple_cmd(node->data.pipeline.cmds[0]);
        //return 0 if failed to execute or 1 if success for the and/or operator
    }
    else if (node->data.pipeline.cmd_count > 1)
    {
        execute_pipeline(node->data.pipeline.cmds[0]);
        //return 0 if failed to execute or 1 if success for the and/or operator
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:57:37 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/01 18:23:03 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_pipe(t_astnode *node, t_env *env, t_ntc **first_node)
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
            execute_builtin(node, env, first_node);
        else
            execute_external_command(node, env, first_node);
        close(pipefd[1]);
        exit(EXIT_SUCCESS);//check if it is the right exit
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);        
        if (node->data.pipeline.cmds)
        execute_pipe(node->data.pipeline.cmds++, env, first_node);
        waitpid(pid, NULL, 0);
    }
    return 0;
}

 //return 0 if failed to execute or 1 if success for the and/or operator
int execute_pipeline(t_astnode *node, t_env *env, t_ntc **first_node)
{
    if (node->data.pipeline.cmd_count == 1)
        return(execute_simple_cmd(node->data.pipeline.cmds[0], env, first_node));
    else if (node->data.pipeline.cmd_count > 1)
        return(execute_pipeline(node->data.pipeline.cmds[0], env, first_node));
    return (0);
}

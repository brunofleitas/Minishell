/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14-execute_external.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:59:53 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/01 18:17:33 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_external_command(t_astnode *node, t_env *env, t_ntc **first_node)
{
    pid_t   pid;
    char    **args;
    char    *path;

    args = get_args(node);
    path = get_path(node, env);
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        if (execve(path, args, env->var) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
    return 0;
}
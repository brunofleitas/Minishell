/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:47:55 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 12:39:03 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

void print_error(const char *msg)
{
    write(STDERR_FILENO, msg, strlen(msg));
}

int builtin_exit(t_ma *ma, char **args)
{
    int exit_code = 0;
    char *trimmed;

    trimmed = ft_strtrim(args[1], "\"", &(ma->first_node));
    //printf("exit code: %s\n", (args[1]));
    //printf("exit code: %s\n", trimmed);
    //printf("exit code: %d\n", ft_atoi(args[1]));
    if (args[1] == NULL)
        exit_code = 0;
    else if (args[2] != NULL)
    {
        print_error("exit: too many arguments\n");
        exit_code = 1;
    }
    else if (!ft_atoi(trimmed))
    {
        print_error("exit: numeric argument required\n");
        exit_code = 2;
    }
    else
    {
        exit_code = ft_atoi(trimmed) % 256;
    }
    free_memory(&(ma->first_node));
    free_memory(&(ma->first_env));
    clear_history();
    exit(exit_code);
}
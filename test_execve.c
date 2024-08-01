/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:26:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/01 11:46:34 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *args[3];

    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nombre_del_archivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    args[0] = "/bruno/cat";
    args[1] = argv[1];
    args[2] = NULL;
    if (execve("/bin/cat", args, NULL) == -1)
    {
        perror("execve"); 
        exit(EXIT_FAILURE);
    }
    return (0);
}
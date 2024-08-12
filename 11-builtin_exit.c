/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:47:55 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/12 01:49:13 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_exit(t_ma *ma)
{
    free(ma->input);
    free_memory(&(ma->first_node));
    free_memory(&(ma->first_env));
    clear_history();
    exit(0);
}
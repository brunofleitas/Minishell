/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17-builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/26 02:57:41 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    env: Array of environment variables.
    first_node: Double pointer to the first t_ntc node.
  Return value:
    Pointer to a string containing all environment variables, 
    each followed by a newline.
  Description:
    Concatenates all environment variables into a single string, 
    each followed by a newline character. Allocates memory for 
    the resulting string and handles errors if memory allocation 
    fails.
*/
char	*builtin_env(char **env, t_ntc **first_node)
{
	int		i;
	size_t	total_length;
	char	*result;
	char	*temp;

	i = 0;
	total_length = 0;
	while (env[i] != NULL)
	{
		total_length += ft_strlen(env[i]) + 1;
		i++;
	}
	result = g_c(first_node, (total_length + 1) * sizeof(char *))->data;
	if (!result)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		ft_strlcat(result, env[i], total_length + 1);
		ft_strlcat(result, "\n", total_length + 1);
		i++;
	}
	return (result);
}

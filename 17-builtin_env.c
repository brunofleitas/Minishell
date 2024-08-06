/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17-builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/06 11:28:38 by bfleitas         ###   ########.fr       */
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
int	builtin_env(char **args, t_env **env, t_ntc **first_node)
{
	int		i;
	size_t	total_length;
	char	*result;

	i = 0;
	total_length = 0;
	if (args[1] != NULL)
	{
		printf("env: too many arguments\n");
		return (1);
	}
	//print the environment variables
	

	while ((*env)->var[i] != NULL)
	{
		total_length += ft_strlen((*env)->var[i]) + 1;
		i++;
	}
	result = g_c(first_node, (total_length + 1) * sizeof(char *))->data;
	if (!result)
		return (1);
	i = 0;
	while ((*env)->var[i] != NULL)
	{
		ft_strlcat(result, (*env)->var[i], total_length + 1);
		ft_strlcat(result, "\n", total_length + 1);
		i++;
	}
	if (result)
	{
		printf("%s", result);
		return (0);
	}
	return (1);
}

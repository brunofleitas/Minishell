/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-build_env_structure.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:53:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/06 15:03:22 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static char	**allocate_env(t_ntc **first_node, int count)
{
	char	**new_envp;

	new_envp = (char**)g_c(first_node, (count + 1) * sizeof(char *))->data;
	if (!new_envp)
	{
		perror("malloc");
		return (NULL);
	}
	return (new_envp);
}
/*
static void	free_env_vars(t_ntc **first_node, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		free_ntc_prior(first_node, env->var[i]);
		i++;
	}
	//free_ntc_prior(first_node, env);
}
*/
t_env	*duplicate_vars(t_ntc **first_node, char **envp)
{
	t_env	*env;
	int		i;

	env = g_c(first_node, sizeof(t_env))->data;
	env->count = count_env_vars(envp);
	env->var = allocate_env(first_node, env->count);
	if (!env->var)
		return (env);
	i = 0;
	while (i < env->count)
	{
		env->var[i] = ft_strdup_g_c(envp[i], first_node);
		if (!env->var[i])
		{
			perror("ft_strdup_g_c");
			free_memory(first_node);
			exit(1);
			//free_env_vars(first_node, env);
		}
		i++;
	}
	env->var[env->count] = NULL;
	//print_env(env);
	return (env);
}

void	print_env(t_env *env)
{
	int i;

	i = 0;
	while (env->var[i])
	{
		printf("%s\n", env->var[i]);
		i++;
	}
}
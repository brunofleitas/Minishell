/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-build_env_structure.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:53:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/26 12:16:07 by bfleitas         ###   ########.fr       */
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

	new_envp = g_c(first_node, (count + 1) * sizeof(char *))->data;
	if (!new_envp)
	{
		perror("malloc");
		return (NULL);
	}
	return (new_envp);
}

static void	free_env_vars(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		free(env->var[i]);
		i++;
	}
	free(env->var);
}

t_env	duplicate_vars(t_ntc **first_node, char **envp)
{
	t_env	env;
	int		i;

	env.count = count_env_vars(envp);
	env.var = allocate_env(first_node, env.count);
	if (!env.var)
		return (env);
	i = 0;
	while (i < env.count)
	{
		env.var[i] = ft_strdup_g_c(envp[i], first_node);
		if (!env.var[i])
		{
			perror("ft_strdup_g_c");
			free_env_vars(&env);
		}
		i++;
	}
	env.var[env.count] = NULL;
	return (env);
}

void	print_env(t_env env)
{
	int i;

	i = 0;
	while (env.var[i])
	{
		printf("%s\n", env.var[i]);
		i++;
	}
}
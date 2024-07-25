/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-builtins_without_output.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:30:58 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/25 17:35:37 by bfleitas         ###   ########.fr       */
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

static int	find_env_var(t_env *env, char *var)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	i = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->var[i], var, len) == 0 && env->var[i][len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (0);
}

static int	update_env_var(t_env *env, int i, const char *var,
		t_ntc **first_node)
{
	free(env->var[i]);
	env->var[i] = ft_strdup_g_c(var, first_node);
	if (!env->var[i])
	{
		perror("ft_strdup_g_c");
		return (0);
	}
	return (1);
}

static int	add_env_var(t_env *env, char *var, t_ntc **first_node)
{
	char	**new_var;

	new_var = realloc(env->var, (env->count + 2) * sizeof(char *));
	if (!new_var)
	{
		perror("realloc");
		return (0);
	}
	env->var = new_var;
	env->var[env->count] = ft_strdup_g_c(var, first_node);
	if (!env->var[env->count])
	{
		perror("ft_strdup_g_c");
		return (0);
	}
	env->count++;
	env->var[env->count] = NULL;
	return (1);
}

int	builtin_export(t_env *env, char *var, t_ntc **first_node)
{
	int	i;

	i = find_env_var(env, var);
	if (i)
		return (update_env_var(env, i, var, first_node));
	return (add_env_var(env, var, first_node));
}

static int	unset_var(t_env *env, const char *name)
{
	int i;

	i = find_env_var(env, name);
    if (i == 0)
		return (0);
	free(env->var[i]);
	while (i < env->count - 1)
	{
		env->var[i] = env->var[i + 1];
		i++;
	}
	env->var[env->count - 1] = NULL;
	env->count = env->count - 1;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18-builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:49:35 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/27 16:41:45 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_var_unset(t_env **env, char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (*env)->count)
	{
		while (name[j] && name[j] == (*env)->var[i][j])
			j++;
		if (name[j] == '\0' && (*env)->var[i][j] == '=')
			return (i);
		i++;
	}
	return (1);
}

int	remove_env_var(t_env **env, char *name)
{
	int	i;

	i = find_env_var_unset(env, name);
	if (i == 0)
		return (1);
	while (i < (*env)->count - 1)
	{
		(*env)->var[i] = (*env)->var[i + 1];
		i++;
	}
	(*env)->var[(*env)->count - 1] = NULL;
	(*env)->count = (*env)->count - 1;
	return (0);
}

static int	check_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": invalid parameter name\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	builtin_unset(char **args, t_ma *ma)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!check_for_equal(args[i]))
		{
			while (args[i])
			{
				if (find_env_var_unset(&ma->env, args[i]) != 0)
					remove_env_var(&ma->env, args[i]);
				i++;
			}
			break ;
		}
		if (find_env_var_unset(&ma->env, args[i]) != 0)
			remove_env_var(&ma->env, args[i]);
		i++;
	}
	exit_or_setexit(0,0, ma);
}

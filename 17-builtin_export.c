/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17-builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:56:05 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/27 18:04:02 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var(char *var)
{
	if (!ft_isalpha(*var) && *var != '_')
		return (0);
	var++;
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
			return (0);
		var++;
	}
	return (1);
}

int	find_env_var(t_env **env, char *var)
{
	int	len;
	int	i;

	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	i = 0;
	while (i < (*env)->count)
	{
		if (ft_strncmp((*env)->var[i], var, len) == 0
			&& (*env)->var[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	update_env_var(int i, const char *var, t_ma *ma)
{
	ma->env->var[i] = ft_strdup_g_c(var, &(ma->first_env));
	if (!(ma->env->var[i]))
	{
		write(2, "ft_strdup_g_c error\n", 20);
		return (1);
	}
	return (0);
}

static int	add_env_var(char *var, t_ma *ma)
{
	char	**new_var;

	new_var = ft_realloc_g_c(&(ma->first_env), ma->env->var, (ma->env->count
				+ 2) * sizeof(char *));
	if (!new_var)
	{
		perror("realloc");
		return (1);
	}
	ma->env->var = new_var;
	ma->env->var[ma->env->count] = ft_strdup_g_c(var, &(ma->first_env));
	if (!(*ma->env->var[ma->env->count]))
	{
		write(2, "ft_strdup_g_c error\n", 20);
		return (1);
	}
	ma->env->count++;
	ma->env->var[ma->env->count] = NULL;
	return (0);
}

void	builtin_export(char **args, t_ma *ma)
{
	char	**tmp;
	int		i;
	char	*var;

	tmp = args;
	tmp++;
	while (*tmp)
	{
		var = *tmp;
    if (!is_valid_var(var))
    {
	  write(2, "minishell: export: `", 20);
	  write(2, var, ft_strlen(var));
      write(2, "': not a valid identifier", 25);
      exit_or_setexit(1, 0, ma);
      return;
    }
		i = find_env_var(&(ma->env), var);
			  if (i >= 0)
	  {
    	if (!update_env_var(i, var,  ma))
      {
        exit_or_setexit(0,0, ma);   
        return;
      }
}
	  else
    {
	    if (!add_env_var(var, ma))
      {
        exit_or_setexit(0,0, ma);
        return;
      }
    }
		tmp++;
	}
	exit_or_setexit(0,0, ma);
}

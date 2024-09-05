/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17-builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:56:05 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/05 15:28:47 by bfleitas         ###   ########.fr       */
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
		return (0);
	}
	ma->env->var = new_var;
	ma->env->var[ma->env->count] = ft_strdup_g_c(var, &(ma->first_env));
	if (!(*ma->env->var[ma->env->count]))
	{
		write(2, "ft_strdup_g_c error\n", 20);
		return (0);
	}
	ma->env->count++;
	ma->env->var[ma->env->count] = NULL;
	return (1);
}

// void print_env(t_env *env)
// {
// 	int i;

// 	i = 0;
// 	while (i < env->count)
// 	{
// 		write(1, "declare -x ", 11);
// 		write(1, env->var[i], ft_strlen(env->var[i]));
// 		write(1, "\n", 1);
// 		i++;
// 	}
// }

#include <stdlib.h>

// Function to swap two environment variables
void swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void print_env(t_env *env)
{
    int i;
    int j;
    int sorted;
    char **sorted_env;
	int len;

    sorted_env = (char **)malloc(sizeof(char *) * env->count);
    if (!sorted_env)
        return;
    i = 0;
    while (i < env->count)
    {
        sorted_env[i] = env->var[i];
        i++;
    }
    i = 0;
    sorted = 0;
    while (i < env->count - 1)
    {
        j = 0;
        while (j < env->count - i - 1)
        {
            if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
            {
                swap(&sorted_env[j], &sorted_env[j + 1]);
                sorted = 1;
            }
            j++;
        }
        if (!sorted)
            break;
        i++;
    }
    i = 0;
    while (i < env->count)
    {
		len = 0;
        write(1, "declare -x ", 11);
		while (sorted_env[i][len] && sorted_env[i][len] != '=')
			len++;
        write(1, sorted_env[i], len);
		if (sorted_env[i][len] == '=')
        {
            write(1, "=", 1);
            len++;
            write(1, "\"", 1);
			int k = len;
            while (sorted_env[i][k])
            {
                if (sorted_env[i][k] == '"')
                    write(1, "\\", 1);
                write(1, &sorted_env[i][k], 1);
                k++;
            }
            write(1, "\"", 1);
        }
        write(1, "\n", 1);
        i++;
    }
    free(sorted_env);
}


void	builtin_export(char **words_arr, t_ma *ma)
{
	char	**words_cpy;
	int		i;
	// char	*new_var_val;

	if (!words_arr[1])
	{
		print_env(ma->env);
		exit_or_setexit(0, 0, ma);
		return ;
	}
	words_cpy = words_arr;
	words_cpy++;
	while (*words_cpy)
	{
		if (!is_valid_var(*words_cpy))
		{
			write(2, "minishell: export: `", 20);
			write(2, *words_cpy, ft_strlen(*words_cpy));
			write(2, "': not a valid identifier\n", 27);
		}
		else 
		{
			i = find_env_var(&(ma->env), *words_cpy);
			if (i >= 0)
			{
				if (!update_env_var(i, *words_cpy, ma))
				{
					exit_or_setexit(0, 0, ma);
					return ;
				}
			}
			else if (i == -1)
			{
				if (!add_env_var(*words_cpy, ma))
				{
					printf("test add_env_var\n");
					exit_or_setexit(0, 0, ma);
					return ;
				}
			}
		}
		words_cpy++;
	}
	exit_or_setexit(0, 0, ma);
}

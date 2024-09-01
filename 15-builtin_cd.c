/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15-builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:45:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/31 01:17:14 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_var(t_env **env, const char *name, char **value)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while ((*env)->var[i])
	{
		if (ft_strncmp((*env)->var[i], name, name_len) == 0
			&& (*env)->var[i][name_len] == '=')
		{
			*value = (*env)->var[i] + name_len + 1;
			if(value[0][0] == '\0')
				return (-1);// this was added to check if PATH is empty
			return (i);
		}
		i++;
	}
	*value = NULL;
	return (-1);
}

char	*get_cd_path(char **args, t_env **env)
{
	char	*path;

	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		path = get_home_directory(env);
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (args[2] == NULL)
		path = args[1];
	else
	{
		fprintf(stderr, "cd: string not in pwd: %s\n", args[1]);
		return (NULL);
	}
	return (path);
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

int	update_oldpwd(char *current_dir, t_ma *ma)
{
	char	*oldpwd_str;
	char	*temp;
	int		i;

	i = get_env_var(&ma->env, "OLDPWD", &temp);
	if (i == -1)
	{
		add_env_var(ft_strjoin_g_c("OLDPWD=", current_dir, &ma->first_env), ma);
	}
	if (i != -1)
	{
		oldpwd_str = ft_strdup_g_c("", &ma->first_env);
		temp = ft_strjoin_g_c(oldpwd_str, "OLDPWD=", &ma->first_env);
		oldpwd_str = temp;
		temp = ft_strjoin_g_c(oldpwd_str, current_dir, &ma->first_env);
		oldpwd_str = temp;
		if (update_env_var(i, oldpwd_str, ma))
		{
			fprintf(stderr,
				"cd: failed to update OLDPWD environment variable\n");
			return (1);
		}
	}
	return (0);
}

int	update_pwd(t_ma *ma)
{
	char	*pwd_str;
	char	*temp;
	char	new_current_dir[PATH_MAX];
	int		i;

	if (getcwd(new_current_dir, sizeof(new_current_dir)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	i = get_env_var(&ma->env, "PWD", &temp);
	if (i == -1)
	{
		add_env_var(ft_strjoin_g_c("PWD=", new_current_dir, &ma->first_env), ma);
	}
	if (i != -1)
	{
		pwd_str = ft_strdup_g_c("", &ma->first_env);
		temp = ft_strjoin_g_c(pwd_str, "PWD=", &ma->first_env);
		pwd_str = temp;
		temp = ft_strjoin_g_c(pwd_str, new_current_dir, &ma->first_env);
		pwd_str = temp;
		if (update_env_var(i, pwd_str, ma))
		{
			fprintf(stderr, "cd: failed to update PWD environment variable\n");
			return (1);
		}
	}
	return (0);
}

void	builtin_cd(char **args, t_ma *ma)
{
	char	current_dir[PATH_MAX];
	char	*path;
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		write(STDERR_FILENO, "minishell: cd: ", 15);
		write(STDERR_FILENO, "too many arguments\n", 19);
		exit_or_setexit(1, 0, ma);
		return ;
	}
	if (args[1] && strcmp(args[1], "") == 0)
		return ;
	path = get_cd_path(args, &ma->env);
    if (!path || !validate_cd_path(path))
    {
        exit_or_setexit(1, 0, ma);
        return;
    }
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		exit_or_setexit(1, 0, ma);
		return ;
	}
    if (change_directory(path))
    {
        exit_or_setexit(1, 0, ma);
        return;
    }
    if (update_env_variables(current_dir, ma))
    {
        exit_or_setexit(1, 0, ma);
        return;
    }
    exit_or_setexit(0,0, ma);
}

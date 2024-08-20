/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:45:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 00:22:03 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid_path(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
	{
		perror("cd");
		return (0);
	}
	if (!S_ISDIR(sb.st_mode)) //CHECK IF IT IS ALLOWED
	{
		fprintf(stderr, "cd: not a directory: %s\n", path);
		return (0);
	}
	return (1);
}

static int	get_env_var(t_env **env, const char *name, char **value)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = strlen(name);
	while ((*env)->var[i])
	{
		if (strncmp((*env)->var[i], name, name_len) == 0
			&& (*env)->var[i][name_len] == '=')
		{
			*value = (*env)->var[i] + name_len + 1;
			return (i);
		}
		i++;
	}
	*value = NULL;
	return (-1);
}

static char	*get_home_directory(t_env **env)
{
	char	*home;

	home = NULL;
	get_env_var(env, "HOME", &home);
	return (home);
}

char *get_cd_path(char **args, t_env **env)
{
    char *path;

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

int validate_cd_path(char *path)
{
    if (check_valid_path(path) == 0)
        return 0;
    return 1;
}

int change_directory(char *path)
{
    if (chdir(path) != 0)
	{
        perror("cd");
        return 1;
    }
    return 0;
}


int update_oldpwd(char *current_dir, t_ma *ma)
{
    char *oldpwd_str;
	char *temp;
    int i;

    i = get_env_var(&ma->env, "OLDPWD", &temp);
    if (i != -1)
	{
        oldpwd_str = ft_strdup_g_c("", &ma->first_env);
        temp = ft_strjoin_g_c(oldpwd_str, "OLDPWD=", &ma->first_env);
        oldpwd_str = temp;
        temp = ft_strjoin_g_c(oldpwd_str, current_dir, &ma->first_env);
        oldpwd_str = temp;
        if (update_env_var(i, oldpwd_str, ma))
		{
            fprintf(stderr, "cd: failed to update OLDPWD environment variable\n");
            return (1);
        }
    }
    return (0);
}

int update_pwd(t_ma *ma)
{
    char *pwd_str;
	char *temp;
    char new_current_dir[PATH_MAX];
    int i;

    if (getcwd(new_current_dir, sizeof(new_current_dir)) == NULL)
    {
        perror("getcwd");
        return (1);
    }
    i = get_env_var(&ma->env, "PWD", &temp);
    if (i != -1)
    {
        pwd_str = ft_strdup_g_c("", &ma->first_env);
        temp = ft_strjoin_g_c(pwd_str, "PWD=",  &ma->first_env);
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

int update_env_variables(char *current_dir, t_ma *ma)
{
    if (update_oldpwd(current_dir, ma))
        return 1;
    if (update_pwd(ma))
        return 1;
    return 0;
}

int builtin_cd(char **args, t_ma *ma)
{
    char current_dir[PATH_MAX];
    char *path;
    int i;

    i = 0;
    while (args[i])
        i++;
    if (i > 2)
    {
        write(STDERR_FILENO, " too many arguments\n", 19);
        return (1);
    }
    path = get_cd_path(args, &ma->env);
    if (!path || !validate_cd_path(path))
        return (1);
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("getcwd");
        return (1);
    }
    if (change_directory(path))
        return (1);
    if (update_env_variables(current_dir, ma))
        return (1);
    return (0);
}


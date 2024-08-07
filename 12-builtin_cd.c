/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:45:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/07 12:56:56 by bfleitas         ###   ########.fr       */
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


int update_oldpwd(t_env **env, char *current_dir, t_ntc **first_node)
{
    char *oldpwd_str;
	char *temp;
    int i;

    i = get_env_var(env, "OLDPWD", &temp);
    if (i != -1)
	{
        oldpwd_str = ft_strdup_g_c("", first_node);
        temp = ft_strjoin_g_c(oldpwd_str, "OLDPWD=", first_node);
        oldpwd_str = temp;
        temp = ft_strjoin_g_c(oldpwd_str, current_dir, first_node);
        oldpwd_str = temp;
        if (update_env_var(env, i, oldpwd_str, first_node))
		{
            fprintf(stderr, "cd: failed to update OLDPWD environment variable\n");
            return (1);
        }
    }
    return (0);
}

int update_pwd(t_env **env, t_ntc **first_node)
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
    i = get_env_var(env, "PWD", &temp);
    if (i != -1)
    {
        pwd_str = ft_strdup_g_c("", first_node);
        temp = ft_strjoin_g_c(pwd_str, "PWD=", first_node);
        pwd_str = temp;
        temp = ft_strjoin_g_c(pwd_str, new_current_dir, first_node);
        pwd_str = temp;
        if (update_env_var(env, i, pwd_str, first_node))
        {
            fprintf(stderr, "cd: failed to update PWD environment variable\n");
            return (1);
        }
    }
    return (0);
}

int update_env_variables(t_env **env, char *current_dir, t_ntc **first_node)
{
    if (update_oldpwd(env, current_dir, first_node))
        return 1;
    if (update_pwd(env, first_node))
        return 1;
    return 0;
}

int builtin_cd(char **args, t_env **env, t_ntc **first_node)
{
    char current_dir[PATH_MAX];
    char *path;

    path = get_cd_path(args, env);
    if (!path)
        return (1);
	if (!validate_cd_path(path))
        return (1);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("getcwd");
        return (1);
    }
    if (change_directory(path))
        return (1);
    if (update_env_variables(env, current_dir, first_node))
        return (1);
    return (0);
}

/*
int	builtin_cd(char **args, t_env **env, t_ntc **first_node)
{
	char	current_dir[PATH_MAX];
	char	*path;
	char	*oldpwd;
	char	*pwd;
	int		i;
  char *oldpwd_str;
	char *pwd_str;
  char *temp;

	oldpwd = NULL;
	pwd = NULL;
  //checks if the path is null or if the path is ~ and sets the path to the home directory
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		path = get_home_directory(env);
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
  //if the path is not null or ~, set the path to the argument
	else if (args[2] == NULL)
		path = args[1];
  //if there is more than one argument, print an error message
  else 
  {
    fprintf(stderr, "cd: string not in pwd: %s\n", args[1]);
    return (1);
  }
  //checks if the path is valid
	if (check_valid_path(path) == 0)
		return (1);
  //gets the current directory
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
  //changes the directory to the path
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
  //gets the index of the OLDPWD variable
	i = get_env_var(env, "OLDPWD", &oldpwd);
  //if the index is not -1, update the OLDPWD variable
	if (i != -1)
	{
    oldpwd_str = ft_strdup_g_c("", first_node);
    temp = ft_strjoin_g_c(oldpwd_str, "OLDPWD=", first_node);
    oldpwd_str = temp;
    temp = ft_strjoin_g_c(oldpwd_str, current_dir, first_node);
    oldpwd_str = temp;
		if (update_env_var(env, i, oldpwd_str, first_node))
		{
			fprintf(stderr, "cd: failed to update OLDPWD environment variable\n");
			return (1);
		}
	}
  //gets the index of the PWD variable
  if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
  //if the index is not -1, update the PWD variable
	i = get_env_var(env, "PWD", &pwd);
	if (i != -1)
	{
    pwd_str = ft_strdup_g_c("", first_node);
    temp = ft_strjoin_g_c(pwd_str, "PWD=", first_node);
    pwd_str = temp;
    temp = ft_strjoin_g_c(pwd_str, current_dir, first_node);
    pwd_str = temp;
		if (update_env_var(env, i, pwd_str, first_node))
		{
			fprintf(stderr, "cd: failed to update PWD environment variable\n");
			return (1);
		}
	}
	return (0);
}*/

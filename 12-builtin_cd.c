/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:45:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/06 15:06:26 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_valid_path(char *path)
{
  struct stat sb;

  if (stat(path, &sb) == -1)
  {
    perror("cd");
    return (0);
  }
  if (!S_ISDIR(sb.st_mode))
  {
    ft_putstr_fd("cd: not a directory: ", 2);
    ft_putstr_fd(path, 2);
    ft_putstr_fd("\n", 2);
    return (0);
  }
  return (1); 
}

static char  *get_env_var(char *name, t_env **env)
{
  int	i;
  char	*value;

  i = 0;
  while ((*env)->var[i])
  {
    if (ft_strncmp((*env)->var[i], name, ft_strlen(name)) == 0)
    {
      value = ft_strchr((*env)->var[i], '=') + 1;
      return (value);
    }
    i++;
  }
  return (NULL);
}

/*
  Parameters:
    path: Path to change the current directory to.
    env: Pointer to the environment variables.
    first_node: Pointer to the first t_ntc node.
  Return value:
    None.
  Description:
    Changes the current working directory to the specified path.
    Updates the PWD environment variable with the new directory path.
    Handles errors for changing the directory and getting the current 
    directory. Allocates memory for the new PWD value and exports it 
    to the environment variables.
*/
static int change_directory(char **args, char *path, t_ma *ma)
{
	char    cwd[PATH_MAX];
	char    *new_pwd;
  size_t  len;

	if (chdir(path) == -1)
  {
		perror("error chdir");
    return (1);
  }
  if (!getcwd(cwd, sizeof(cwd)))
  {
		perror("getcwd");
    return (1);
  }
  len = 4 + ft_strlen(cwd) + 1;
	new_pwd = g_c(&(ma->first_node), (4 + ft_strlen(cwd) + 1))->data;
	if (!new_pwd)
  {
		perror("malloc");
    return (1);
  }
	ft_strlcpy(new_pwd, "PWD=", len);
	ft_strlcat(new_pwd, cwd, len);
	builtin_export(args, ma);
	free_ntc_prior(&(ma->first_node), new_pwd);
  return (0);
}

/*
  Parameters:
    node: Pointer to the AST node.
    first_node: Pointer to the first t_ntc node.
    env: Pointer to the environment variables.
  Return value:
    None.
  Description:
    Handles the "cd" built-in command. Changes the directory to the 
    specified path. If no path is provided, changes to the home directory. 
    Handles errors for too many arguments and invalid paths.
*/
int	builtin_cd(char **args, t_ma *ma)
{
  char    *path;

  path = args[1];
  if (!args[1])
  {
      path = get_env_var("HOME", &(ma->env));
      return (change_directory(args, path, ma));
  }
  else if(args[2])
  {
      perror("cd: too many arguments");
      return (1);
  }
  else if(check_valid_path(path))
  {
      path = args[1];
      return (change_directory(args, path, ma));
  }
  else 
    return (1);
}

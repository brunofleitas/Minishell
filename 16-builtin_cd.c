/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:45:41 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/26 02:59:58 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static void change_directory(char *path, t_env *env, t_ntc *first_node)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;
    size_t  len;

	if (chdir(path) == -1)
		perror("errpr chdir");
	if (!getcwd(cwd, sizeof(cwd)))
		perror("getcwd");
    len = 4 + ft_strlen(cwd) + 1;
	new_pwd = g_c(first_node, (4 + ft_strlen(cwd) + 1));
	if (!new_pwd)
		perror("malloc");
	ft_strlcpy(new_pwd, "PWD=", len);
	ft_strlcat(new_pwd, cwd, len);
	export_var(env, new_pwd);
	free(new_pwd);
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
void	builtin_cd(t_astnode *node, t_ntc *first_node, t_env *env)
{
    t_astnode    *path;

    path = node->data.simple_cmd.words->data.word.next;
    if (!path->data.word.value)
    {
        path = get_env_var("HOME", env);
        change_directory(path , env, first_node);
    }
    else if(path->data.word.next)
        perror("cd: too many arguments");
    else //check if path is valid
        change_directory(path->data.word.value, env, first_node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-bultin_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:56:05 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/26 02:56:42 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    env: Pointer to the environment variables.
    var: Variable name to find.
  Return value:
    Index of the environment variable if found, 0 otherwise.
  Description:
    Searches for an environment variable by name. Compares each 
    variable up to the length of the given name. Returns the index 
    of the variable if a match is found, otherwise returns 0.
*/
int	find_env_var(t_env *env, char *var)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	i = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->var[i], var, len) == 0 && env->var[i][len] == '=')
			return (i);
		i++;
	}
	return (0);
}

/*
  Parameters:
    env: Pointer to the environment variables.
    i: Index of the variable to update.
    var: New value for the variable.
    first_node: Double pointer to the first t_ntc node.
  Return value:
    None.
  Description:
    Updates an existing environment variable at the given index.
    Frees the old value and duplicates the new value. Handles 
    errors if memory duplication fails.
*/
static void	update_env_var(t_env *env, int i, const char *var,
		t_ntc **first_node)
{
	free(env->var[i]);
	env->var[i] = ft_strdup_g_c(var, first_node);
	if (!env->var[i])
		perror("ft_strdup_g_c");
}

/*
  Parameters:
    env: Pointer to the environment variables.
    var: Variable name to add.
    first_node: Double pointer to the first t_ntc node.
  Return value:
    None.
  Description:
    Adds a new environment variable. Reallocates memory for the 
    environment variables array, duplicates the variable name, 
    and updates the environment variable count. Handles errors 
    if memory allocation fails.
*/
static void	add_env_var(t_env *env, char *var, t_ntc **first_node)
{
	char	**new_var;

	new_var = realloc(env->var, (env->count + 2) * sizeof(char *));
	if (!new_var)
		perror("realloc");
	env->var = new_var;
	env->var[env->count] = ft_strdup_g_c(var, first_node);
	if (!env->var[env->count])
		perror("ft_strdup_g_c");
	env->count++;
	env->var[env->count] = NULL;
}

/*
  Parameters:
    node: Pointer to the abstract syntax tree (AST) node.
    first_node: Double pointer to the first node of type t_ntc.
    env: Pointer to the environment variables structure.
  Return value:
    None.
  Description:
    Handles the "export" built-in shell command. Extracts the 
    variable name from the simple command in the AST node. 
    Searches for the variable in the environment variables. 
    If the variable exists, it updates the variable's value. 
    If the variable does not exist, it adds the variable to 
    the environment.
*/
void	builtin_export(t_astnode *node, t_ntc **first_node, t_env *env)
{
	int			i;
	t_astnode	*tmp;
	char		*var;

	tmp = node->data.simple_cmd.words;
	var = tmp->data.word.next->data.word.value;
	i = find_env_var(env, var);
	if (i)
		update_env_var(env, i, var, first_node);
	else
		add_env_var(env, var, first_node);
}

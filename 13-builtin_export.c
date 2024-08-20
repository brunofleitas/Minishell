/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:56:05 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 17:56:44 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_var(char *var)
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
		if (ft_strncmp((*env)->var[i], var, len) == 0 && (*env)->var[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
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
int	update_env_var(int i, const char *var, t_ma *ma)
{
	//free_ntc_prior(first_node, (*env)->var[i]);
	ma->env->var[i] = ft_strdup_g_c(var, &(ma->first_env));
	if (!(ma->env->var[i]))
  {
		write(2, "ft_strdup_g_c error\n", 20);
    return (1);
  }
  return (0);
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
static int	add_env_var(char *var, t_ma *ma)
{
	char	**new_var;
  //printf("add_env_var-----------------------------START\n");
  //print_env(*env);
  //printf("\n\n\n\n");
	new_var = ft_realloc_g_c(&(ma->first_env), ma->env->var, (ma->env->count + 2) * sizeof(char *));
	if (!new_var)
  {
		//perror("realloc");
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
  //print_env(*env);
  //printf("add_env_var-----------------------------END\n");
  return (0);
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
int	builtin_export(char **args, t_ma *ma)
{
	char    **tmp;
  int     i;
	char    *var;
  //int     status;

	tmp = args;
  tmp++;
  while (*tmp)
  {
    var = *tmp;
    if (!is_valid_var(var))
    {
      write(2, " not a valid identifier", 23);
      return (1);
    }
	  i = find_env_var(&(ma->env), var);
	  if (i >= 0)
	  {
    	if (!update_env_var(i, var,  ma))
        return(EXIT_FAILURE);
    }
	  else
    {
	    if (!add_env_var(var, ma))
      {
        return(EXIT_FAILURE);
      }
    }
    tmp++;
  }
  return (EXIT_SUCCESS);
}

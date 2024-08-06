/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16-builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:00 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/04 13:54:59 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    first_node: Double pointer to the first t_ntc node.
  Return value:
    Pointer to a string containing the current working directory,
    or NULL if an error occurs.
  Description:
    Retrieves the current working directory using getcwd. If 
    successful, duplicates the directory string and returns it. 
    Prints an error message if getcwd fails.
*/
int	builtin_pwd(char **args, t_ma *ma)
{
	char	cwd[PATH_MAX];

  if (args[1] != NULL)
  {
    ft_printf("pwd: too many arguments\n");
    return (1);
  }
	if (getcwd(cwd, sizeof(cwd)) != NULL)
  {
		printf("%s\n", ft_strdup_g_c(cwd, &(ma->first_node)));
    return (0);
  }
  else
  {
		ft_printf("getcwd() error");
	  return (1);
  }
}

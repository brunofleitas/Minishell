/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20-builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:00 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/27 16:26:39 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(char **args, t_ma *ma)
{
	char	cwd[PATH_MAX];

  (void)args;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
  {
		ft_printf("%s\n", ft_strdup_g_c(cwd, &(ma->first_node)));
    exit_or_setexit(0,0, ma);
  }
  else
  {
    write(STDERR_FILENO, "getcwd() error\n", 14);
	  exit_or_setexit(1,0, ma);
  }
}

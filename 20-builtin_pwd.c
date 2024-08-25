/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20-builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:00 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/25 08:29:10 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **args, t_ma *ma)
{
	char	cwd[PATH_MAX];

	(void)args;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", ft_strdup_g_c(cwd, &(ma->first_node)));
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_printf("getcwd() error");
		return (EXIT_FAILURE);
	}
}

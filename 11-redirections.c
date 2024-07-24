/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:51:48 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/24 19:13:17 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(const char *output, const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("open() error");
		return ;
	}
	if (write(fd, output, ft_strlen(output)) == -1)
		ft_printf("write() error");
	close(fd);
}

void	redirect_output_append(const char *output, const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf("open() error");
		return ;
	}
	if (write(fd, output, ft_strlen(output)) == -1)
		ft_printf("write() error");
	close(fd);
}

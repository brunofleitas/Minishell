/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18-redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:52:15 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/26 02:59:05 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    output: String to write to the file.
    file_name: Name of the file to write to.
  Return value:
    None.
  Description:
    Opens the specified file for writing, creating it if it doesn't
    exist, and truncating it if it does. Writes the output string 
    to the file. Handles errors for opening and writing to the file.
*/
void	redirect_output(const char *output, const char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("open() error");
		return ;
	}
	if (write(fd, output, ft_strlen(output)) == -1)
		ft_printf("write() error");
	close(fd);
}

/*
  Parameters:
    output: String to append to the file.
    file_name: Name of the file to append to.
  Return value:
    None.
  Description:
    Opens the specified file for appending, creating it if it doesn't
    exist. Appends the output string to the file. Handles errors for 
    opening and writing to the file.
*/
void	redirect_output_append(const char *output, const char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf("open() error");
		return ;
	}
	if (write(fd, output, ft_strlen(output)) == -1)
		ft_printf("write() error");
	close(fd);
}

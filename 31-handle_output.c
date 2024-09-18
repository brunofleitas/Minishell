/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31-handle_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:53:13 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:20:53 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Redirects output to a file in truncate mode.
 *
 * This function opens the specified file in truncate mode, meaning the file 
 * is overwritten if it exists. It redirects the output to the given file 
 * descriptor (`fd_num`). If the file cannot be opened due to permission issues, 
 * an error message is printed. The output is redirected using `dup2`, and 
 * the file descriptor is closed after use.
 *
 * @param file_name The name of the file to redirect output to.
 * @param fd_num The file descriptor to redirect (e.g., STDOUT_FILENO).
 * @param ma Pointer to the structure containing metadata for error messages.
 * @return 1 on success, 0 on failure.
 */
int	redirect_output(char *file_name, int fd_num, t_ma *ma)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		write(2, ma->program, ma->l_program);
		write(2, file_name, ft_strlen(file_name));
		write(2, ": Permission denied\n", 20);
		return (0);
	}
	if (dup2(fd, fd_num) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

/**
 * @brief Redirects output to a file in append mode.
 *
 * This function opens the specified file in append mode and redirects the 
 * output to the given file descriptor (`fd_num`). If the file cannot be 
 * opened due to permission issues, it prints an error message. The output 
 * is redirected using `dup2`, and the file descriptor is closed after use.
 *
 * @param file_name The name of the file to append output to.
 * @param fd_num The file descriptor to redirect (e.g., STDOUT_FILENO).
 * @param ma Pointer to the structure containing metadata for error messages.
 * @return 1 on success, 0 on failure.
 */
int	redirect_output_append(char *file_name, int fd_num, t_ma *ma)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		write(2, ma->program, ma->l_program);
		write(2, file_name, ft_strlen(file_name));
		write(2, ": Permission denied\n", 21);
		return (0);
	}
	if (dup2(fd, fd_num) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32-handle_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:53:04 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:21:49 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*gnl(int fd);

/**
 * @brief Redirects input from a file.
 *
 * This function opens the specified file for reading and redirects the 
 * input to the file using `dup2`. If the file cannot be opened (e.g., 
 * if it does not exist), it prints an error message. The input redirection 
 * replaces `STDIN_FILENO`. The file descriptor is closed after redirection.
 *
 * @param file_name The name of the file to redirect input from.
 * @param ma Pointer to the structure containing metadata, including program 
 * 			 name for error messages.
 * @return 1 on success, 0 on failure.
 */
int	redirect_input(char *file_name, t_ma *ma)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		write(2, ma->program, ma->l_program);
		write(2, file_name, ft_strlen(file_name));
		write(2, ": No such file or directory\n", 28);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

/**
 * @brief Processes a line for heredoc input, handling environment variables 
 * 		  and exit status.
 *
 * This function processes a line of heredoc input, writing it to the temporary 
 * file while handling special cases such as expanding environment variables 
 * and replacing the exit status (`$?`). It iterates through the line and 
 * applies the appropriate handlers for these cases.
 *
 * @param fd The file descriptor of the temporary file to write to.
 * @param line The input line to process.
 * @param ma Pointer to the structure containing metadata, including environment 
 *           variables and exit status.
 * @return 1 on success.
 */
int	process_line(int fd, char *line, t_ma *ma)
{
	int		i;
	int		len;

	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if (handle_exit_status(fd, line, &i, ma))
			continue ;
		else if (handle_env_variable(fd, line, &i, ma))
			continue ;
		write(fd, &line[i], 1);
		i++;
	}
	return (1);
}

/**
 * @brief Writes heredoc input to a temporary file until the delimiter is 
 * 		  reached.
 *
 * This function reads input from standard input and writes it to the temporary 
 * file until the specified delimiter is encountered. Each line is processed 
 * and written to the file, followed by a newline. If writing fails at any 
 * point, the function returns failure.
 *
 * @param fd The file descriptor of the temporary file to write to.
 * @param delimiter The string used to mark the end of the heredoc input.
 * @param ma Pointer to the structure containing metadata, including I/O state.
 * @return 1 on success, 0 on failure.
 */
int	write_to_tmp_file(int fd, const char *delimiter, t_ma *ma)
{
	char	*line;

	line = gnl(0);
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		if (!process_line(fd, line, ma))
			return (0);
		write(fd, "\n", 1);
		line = gnl(0);
	}
	return (1);
}

/**
 * @brief Creates a temporary file for heredoc redirection.
 *
 * This function creates a temporary file where heredoc input will be written. 
 * The file is created in truncate mode with restricted permissions (0600). 
 * If writing to the file fails, it closes and deletes the temporary file.
 *
 * @param temp_file_name The name of the temporary file to create.
 * @param delimiter The string used to mark the end of the heredoc input.
 * @param ma Pointer to the structure containing metadata, including I/O state.
 * @return 1 on success, 0 on failure.
 */
int	create_tmp_file(const char *temp_file_name, const char *delimiter,
		t_ma *ma)
{
	int	fd;

	fd = open(temp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		return (0);
	}
	if (!write_to_tmp_file(fd, delimiter, ma))
	{
		close(fd);
		unlink(temp_file_name);
		return (0);
	}
	close(fd);
	return (1);
}

/**
 * @brief Handles a heredoc redirection for a command.
 *
 * This function processes a heredoc redirection by creating a temporary file 
 * that contains the input data up to the specified delimiter. It then redirects 
 * the input to read from this temporary file. After the input is redirected, 
 * the temporary file is deleted using `unlink`.
 *
 * @param delimiter The string used to mark the end of the heredoc input.
 * @param ma Pointer to the structure containing metadata, including temporary 
 *           file management and I/O state.
 * @return 1 on success, 0 on failure.
 */
int	handle_heredoc(const char *delimiter, t_ma *ma)
{
	char	*temp_file_name;

	temp_file_name = give_tmp_name(ma);
	if (!temp_file_name)
		return (0);
	if (!create_tmp_file(temp_file_name, delimiter, ma))
		return (0);
	redirect_input(temp_file_name, ma);
	if (unlink(temp_file_name) == -1)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:30:29 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 15:31:31 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	file_fd;

	// Test writing to standard output
	ft_putchar_fd('A', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	// Open a file for writing
	file_fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	// Test writing to a file
	ft_putchar_fd('B', file_fd);
	ft_putchar_fd('\n', file_fd);
	// Close the file
	if (close(file_fd) == -1)
	{
		perror("Error closing file");
		return (1);
	}
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_putchar_fd` writes a single character to a specified file descriptor. This
means you can use it to display a character on the screen (by writing to
STDOUT), save it in a file, or even send it to a network socket. It's a simple
way to output a character to different places based on the file descriptor you
choose.
*/
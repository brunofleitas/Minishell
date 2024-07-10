/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:42:07 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 15:43:09 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, s + i, 1);
		i++;
	}
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
	ft_putstr_fd("Hello, standard output!\n", STDOUT_FILENO);
	// Open a file for writing
	file_fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	// Test writing to a file
	ft_putstr_fd("Hello, file!\n", file_fd);
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
`ft_putstr_fd` sends a string to a specified destination, like a file or the
console, based on the file descriptor provided. It's useful for displaying
messages or outputting text to files systematically.
*/
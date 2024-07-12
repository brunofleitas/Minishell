/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:36:12 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 15:39:20 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reverse_string(char *str, int length)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = length - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return (str);
}

static char	*populate_string(long num, char *str)
{
	int	i;
	int	rem;
	int	isnegative;

	i = 0;
	isnegative = 0;
	if (num < 0)
	{
		isnegative = 1;
		num = -num;
	}
	str[i++] = '\0';
	while (num != 0)
	{
		rem = num % 10;
		str[i++] = rem + '0';
		num = num / 10;
	}
	if (isnegative)
		str[i++] = '-';
	return (reverse_string(str, i));
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	large;
	char		newchar[12];
	char		*finalchar;

	large = n;
	if (n == 0)
		write(fd, "0", 1);
	else
	{
		finalchar = populate_string(large, newchar);
		while (*finalchar)
		{
			write(fd, finalchar, 1);
			finalchar++;
		}
	}
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void) {
	int file_fd;

	// Test writing numbers to standard output
	ft_putnbr_fd(123, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1); // For readability

	ft_putnbr_fd(-123, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1); // For readability

	ft_putnbr_fd(0, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1); // For readability

	// Open a file for writing
	file_fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1) {
		perror("Error opening file");
		return (1);
	}

	// Test writing numbers to a file
	ft_putnbr_fd(456, file_fd);
	write(file_fd, "\n", 1); // For readability

	ft_putnbr_fd(-456, file_fd);
	write(file_fd, "\n", 1); // For readability

	// Close the file
	if (close(file_fd) == -1) {
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
`ft_putnbr_fd` writes an integer to a specified file descriptor. It can handle
both positive and negative numbers, displaying them correctly as text. For
example, if you want to print the number 42 or -42 to the screen or a file, this
function can do it. It's useful for outputting numbers to various destinations,
like files or the console.
*/
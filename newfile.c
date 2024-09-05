char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:06:28 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/11 13:06:31 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/*
  Parameters:
    input: A string representing the user's input.
  Return value:
    None. This function does not return a value; instead, it processes the input
      within the scope of the program.
  Description:
    This function reads and processes user input continuously until the user
    enters "exit". It uses the readline library to capture user input,
    compares the input against the "exit" cmd, adds the input to the 
	history for convenience, processes the input using a lexer function, and 
	finally frees the memory allocated for the input string after processing. 
	The function also ensures to clear the history at the end of execution.
*/
int	main(int argc, char **argv, char **envp)
{
	char		*input;

    (void)argc;
    (void)argv;
    (void)envp;
    while(1)
    {
		input = !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : readline(">>");
        printf("input: %s\n", input);
    }
	
}

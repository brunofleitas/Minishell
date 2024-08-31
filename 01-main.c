#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01-main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:59:46 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/27 17:03:59 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

//tester: https://github.com/LucasKuhn/minishell_tester/tree/main
//liveshare: https://prod.liveshare.vsengsaas.visualstudio.com/join?0623C96F2899D5C1DD0735373291B02F4DA7
 
void sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    //rl_replace_line("", 0);
    rl_redisplay();
}

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
	t_ma 		ma;
	t_astnode 	*root;

	
	(void)argc;
	(void)argv;
	ma.first_node = NULL;
	ma.first_env = NULL;
	ma.last_exit_status = 0;
	ma.in_child_p = 0;
	ma.env = duplicate_vars(&(ma.first_env), envp);
	int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
	int temp_fd1;
	int temp_fd2;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		ma.input = !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : !isatty(0) ? gnl(0) : readline("minisshell>>");
		if (ma.input == NULL)
        	builtin_exit(&ma, NULL);
		if (ft_strcmp(ma.input, "") != 0)
		{
			!isatty(0) ? 0 : !isatty(0) ? 0 : !isatty(0) ? 0 : !isatty(0) ? 0 : !isatty(0) ? 0 : !isatty(0) ? 0 : add_history(ma.input);
			lexer(&ma);
			if (ma.tkns[0] != NULL)
			{	
				//get_next_token(&ma);
				// printf("test\n");
				root = parser(&ma);
				// printf("test\n");
				//printf("parser end\n");
				execute_ast(root, &ma);
				//printf("test\n");
				// printf("execute_ast end\n");
				//printf("main\n");
				//print_env(env);
			}
			free_memory(&(ma.first_node));
		}
		temp_fd1 = dup(STDIN_FILENO);
		temp_fd2 = dup(STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close (temp_fd1);
		close (temp_fd2);
	}
	// free_memory(&(ma.first_env));
	// clear_history();
	//ft_printf("clear_history was executed\n");
	return (0);
}

/*
 * Next step:
 * Construct a syntax tree, often referred to as an Abstract Syntax Tree (AST).
 * The AST represents the syntactic structure of the parsed input in a 
 * hierarchical tree form, where each node represents a construct occurring 
 * in the source code.
 *
 * The lexer has already segmented the input into tokens and classified them,
 * which is the first step in parsing. The next step, constructing the AST,
 * involves analyzing the sequence of tokens to understand their syntactic 
 * relationships and organizing them into a tree that reflects the commands 
 * and their execution order, including pipelines, redirections, and control 
 * structures.
 *
 * Here's a high-level overview of steps you might take to construct the AST:
 *
 * 1. **Parsing**: Implement a parser that takes the list of tokens produced by 
 *    the lexer and applies grammar rules to organize these tokens into a tree 
 *    structure. This involves recognizing patterns in the sequence of tokens 
 *    that correspond to commands, arguments, operators, etc.
 *
 * 2. **AST Nodes Creation**: Define different types of nodes for your AST, 
 *    corresponding to the constructs in your shell language, such as command 
 *    nodes, pipeline nodes, redirection nodes, and so on.
 *
 * 3. **Building the Tree**: As the parser recognizes the grammar patterns in 
 *    the token sequence, it should create the appropriate AST nodes and link 
 *    them together to build the tree. This involves determining the 
 *    parent-child relationships between nodes based on the syntactic structure 
 *    of the input.
 *
 * 4. **Error Handling**: Implement error handling in the parser to deal with 
 *    syntax errors, providing meaningful error messages to the user.
 *
 * The get_next_token function is used to initialize the index to 0.
 *
 * After constructing the AST, the next steps in the shell's execution process 
 * would involve traversing the AST to interpret or execute the commands 
 * represented by the tree.
 *
 * This process is crucial for a shell because it allows for the correct 
 * interpretation and execution of complex command lines, including handling 
 * of operators, command grouping, and redirections in a way that respects the 
 * intended precedence and associativity of operations.
 */


void __attribute__((destructor)) free_gnl_buffer();

void free_gnl_buffer() { gnl(-1); }


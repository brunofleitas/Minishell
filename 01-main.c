#include <unistd.h>
char	*gnl(int fd);
#include <unistd.h>
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:59:46 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 23:29:02 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Signal handler for SIGINT.
 *
 * This function is called when the SIGINT signal is received. It handles the
 * interruption by writing a newline character to the standard output, moving
 * the readline cursor to a new line, replacing the current line with an empty
 * string, and redisplaying the readline prompt.
 *
 * @param sig The signal number.
 */
void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Initializes the t_ma structure.
 *
 * This function initializes the members of the t_ma structure. It sets the
 * first_node, first_env, and input pointers to NULL, initializes the
 * last_exit_status to 0, and duplicates the environment variables into the
 * env member.
 *
 * @param ma Pointer to the t_ma structure to initialize.
 * @param envp Array of environment variables.
 */
static void	init_ma(t_ma *ma, char **envp)
{
	ma->first_node = NULL;
	ma->first_env = NULL;
	ma->input = NULL;
	ma->last_exit_status = 0;
	ma->env = duplicate_vars(&(ma->first_env), envp);
}

/**
 * @brief Processes the input command.
 *
 * This function processes the input command stored in the t_ma structure. If
 * the input is not an empty string, it adds the input to the history,
 * tokenizes it using the lexer, parses the tokens into an abstract syntax
 * tree (AST), and executes the AST. Finally, it frees the memory allocated
 * for the AST nodes.
 *
 * @param ma Pointer to the t_ma structure containing the input command and
 *           other relevant data.
 */
static void	process_input(t_ma *ma)
{
	t_astnode	*root;

	if (ft_strcmp(ma->input, "") != 0)
	{
		add_history(ma->input);
		lexer(ma);
		if (ma->tkns[0] != NULL)
		{
			root = parser(ma);
			ma->last_exit_status = execute_ast(root, ma);
		}
		free_memory(&(ma->first_node));
	}
}

/**
 * @brief Entry point of the minishell program.
 *
 * This function initializes the minishell environment and enters an
 * infinite loop to read and process user input. It sets up signal
 * handlers for SIGINT and SIGQUIT, initializes the t_ma structure,
 * and uses the readline library to display a prompt and read input
 * from the user. If the input is NULL (EOF), it calls the builtin_exit
 * function to exit the shell. Otherwise, it processes the input
 * command.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param envp Environment variables.
 * @return int Exit status of the program.
 */
int	main(int argc, char **argv, char **envp)
{
	t_ma	ma;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init_ma(&ma, envp);
	while (1)
	{
		ma.input = readline("\x1b[32mminishell>\x1b[0m");
		if (ma.input == NULL)
			builtin_exit(&ma, NULL);
		process_input(&ma);
	}
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

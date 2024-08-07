/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:59:46 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/06 17:27:53 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(void)argc;
	(void)argv;
	char		*input;
	t_ntc		*first_node;
	t_ntc		*first_env;
	t_token		*tkns[1024];
	t_env		*env;
	t_astnode	*root;

	first_node = NULL;
	first_env = NULL;
	env = duplicate_vars(&first_env, envp);
	while (1)
	{
		input = readline(">>");
		if (ft_strcmp(input, "") != 0)
		{
			if (ft_strcmp(input, "exit") == 0)
			{
				free(input);
				break ;
			}
			add_history(input);
			lexer(input, tkns, &first_node);
			get_next_token(tkns, 0);
			root = parser(&first_node, tkns);
			execute_ast(root, &env, &first_node);
			//printf("main\n");
			//print_env(env);
			//free_memory(&first_node);
		}
	}
	//free_memory(&first_env);
	//free_memory(&first_node);
	clear_history();
	return (0);
}
/*
	Next step:
Construct a syntax tree, often referred to as an Abstract Syntax Tree (AST). The AST represents the syntactic structure of the parsed input in a hierarchical tree form, where each node represents a construct occurring in the source code.

The lexer has already segmented the input into tkns and classified them, which is the first step in parsing. The next step, constructing the AST, involves analyzing the sequence of tkns to understand their syntactic relationships and organizing them into a tree that reflects the cmds and their execution order, including pipelines, redirections, and control structures.

Here's a high-level overview of steps you might take to construct the AST:

1. **Parsing**: Implement a parser that takes the list of tkns produced by the lexer and applies grammar rules to organize these tkns into a tree structure. This involves recognizing patterns in the sequence of tkns that correspond to cmds, arguments, operators, etc.

2. **AST Nodes Creation**: Define different types of nodes for your AST, corresponding to the constructs in your shell language, such as cmd nodes, pipeline nodes, redirection nodes, and so on.

3. **Building the Tree**: As the parser recognizes the grammar patterns in the token sequence, it should create the appropriate AST nodes and link them together to build the tree. This involves determining the parent-child relationships between nodes based on the syntactic structure of the input.

4. **Error Handling**: Implement error handling in the parser to deal with syntax errors, providing meaningful error messages to the user.

Get_next_token function is used to initialize the i = 0;

After constructing the AST, the next steps in the shell's execution process would involve traversing the AST to interpret or execute the cmds represented by the tree.

This process is crucial for a shell because it allows for the correct interpretation and execution of complex cmd lines, including handling of operators, cmd grouping, and redirections in a way that respects the intended precedence and associativity of operations.
*/
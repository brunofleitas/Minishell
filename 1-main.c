/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:59:46 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/24 12:39:17 by bfleitas         ###   ########.fr       */
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
    compares the input against the "exit" command, adds the input to the 
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
	t_token		*tokens[1024];
	//t_astnode	*root;

	first_node = NULL;
	while (1)
	{
		//root = NULL;
		input = readline(">>");
		if (input)
		{
			if (ft_strcmp(input, "exit") == 0)
			{
				free(input);
				break ;
			}
			add_history(input);
			lexer(input, &first_node, tokens);
			//root = parse_command_line(&first_node, tokens);
			//free_ast(&root);
			free(input);
		}
		else
			break ;
	}
	clear_history();
	free_memory(&first_node);
	return (0);
}

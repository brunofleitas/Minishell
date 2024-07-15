/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-ast_check_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:43:35 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/15 23:45:19 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Parameters:
    token: A pointer to a t_word structure representing the current token.
  Return value:
    1 if the token is a command, otherwise returns 0.
  Description:
    Checks if the given token represents a command by comparing its key 
    with predefined command tokens.
*/
int is_command(t_word *token)
{
	if (token->key == TOKEN_COMMAND_ECHO || token->key == TOKEN_COMMAND_CD
		|| token->key == TOKEN_COMMAND_PWD || token->key == TOKEN_COMMAND_EXPORT
		|| token->key == TOKEN_COMMAND_UNSET || token->key == TOKEN_COMMAND_ENV)
		return (1);
	return (0);
}

/*
  Parameters:
    token: A pointer to a t_word structure representing the current token.
  Return value:
    1 if the token is an operator, otherwise returns 0.
  Description:
    Checks if the given token represents an operator by comparing its key 
    with predefined operator tokens.
*/
int	is_operator(t_word *token)
{
	if (token->key == TOKEN_PIPE || token->key == TOKEN_AND
		|| token->key == TOKEN_OR)
		return (1);
	return (0);
}

/*
  Parameters:
    token: A pointer to a t_word structure representing the current token.
  Return value:
    1 if the token is a redirection, otherwise returns 0.
  Description:
    Checks if the given token represents a redirection by comparing its key 
    with predefined redirection tokens.
*/
int	is_redirect(t_word *token)
{
	if (token->key == TOKEN_REDIRECT_IN || token->key == TOKEN_REDIRECT_OUT
		|| token->key == TOKEN_REDIRECT_APPEND)
		return (1);
	return (0);
}

/*
  Parameters:
    token: A pointer to a t_word structure representing the current token.
  Return value:
    1 if the token is a variable, otherwise returns 0.
  Description:
    Checks if the given token represents a variable by comparing its key 
    with predefined variable tokens.
*/
int	is_variable(t_word *token)
{
	if (token->key == TOKEN_VARIABLE || token->key == TOKEN_VARIABLE_EXIT)
		return (1);
	return (0);
}

/*
  Parameters:
    token: A pointer to a t_word structure representing the current token.
  Return value:
    1 if the token is a string, otherwise returns 0.
  Description:
    Checks if the given token represents a string by comparing its key 
    with predefined string tokens.
*/
int	is_string(t_word *token)
{
	if (token->key == TOKEN_STRING_SINGLE || token->key == TOKEN_STRING_DOUBLE)
		return (1);
	return (0);
}

/*
  Parameters:
    token: A pointer to a t_word structure representing the current token.
  Return value:
    1 if the token is an argument, otherwise returns 0.
  Description:
    Checks if the given token represents an argument by comparing its key 
    with predefined argument tokens.
*/
int	is_argument(t_word *token)
{
	if (token->key == TOKEN_ARGUMENT)
		return (1);
	return (0);
}

/*
  Parameters:
    token: A pointer to a t_word structure representing the current token.
  Return value:
    1 if the token is a here document, otherwise returns 0.
  Description:
    Checks if the given token represents a here document by comparing its key 
    with predefined here document tokens.
*/
int	is_here_document(t_word *token)
{
	if (token->key == TOKEN_HERE_DOCUMENT)
		return (1);
	return (0);
}

/*
  Parameters:
    token: A pointer to a t_word structure representing the current token.
  Return value:
    1 if the token is an error, otherwise returns 0.
  Description:
    Checks if the given token represents an error by comparing its key 
    with predefined error tokens.
*/
int	is_error(t_word *token)
{
	if (token->key == TOKEN_ERROR)
		return (1);
	return (0);
}
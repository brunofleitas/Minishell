/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-clasify_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:49:28 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/11 23:53:14 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	classify_command(char *value)
{
	if (ft_strcmp(value, "echo") == 0)
		return (TOKEN_COMMAND_ECHO);
	if (ft_strcmp(value, "cd") == 0)
		return (TOKEN_COMMAND_CD);
	if (ft_strcmp(value, "pwd") == 0)
		return (TOKEN_COMMAND_PWD);
	if (ft_strcmp(value, "export") == 0)
		return (TOKEN_COMMAND_EXPORT);
	if (ft_strcmp(value, "unset") == 0)
		return (TOKEN_COMMAND_UNSET);
	if (ft_strcmp(value, "env") == 0)
		return (TOKEN_COMMAND_ENV);
	return (TOKEN_ERROR);
}

static t_token_type	classify_operator(char *value)
{
	if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIRECT_APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HERE_DOCUMENT);
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(value, "&&") == 0)
		return (TOKEN_AND);
	if (ft_strcmp(value, "||") == 0)
		return (TOKEN_OR);
	return (TOKEN_ERROR);
}

static t_token_type	classify_variable(char *value)
{
	if (value[0] == '$' && value[1] == '?')
		return (TOKEN_VARIABLE_EXIT);
	if (value[0] == '$')
		return (TOKEN_VARIABLE);
	return (TOKEN_ERROR);
}

static t_token_type	classify_string(char *value)
{
	if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		return (TOKEN_STRING_SINGLE);
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		return (TOKEN_STRING_DOUBLE);
	return (TOKEN_ERROR);
}

t_token_type	clasify_token(char *value)
{
	int	token_type;

	token_type = classify_command(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	token_type = classify_operator(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	token_type = classify_variable(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	token_type = classify_string(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	if (ft_strlen(value) > 0)
		return (TOKEN_ARGUMENT);
	return (TOKEN_ERROR);
}

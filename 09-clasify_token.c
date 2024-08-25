/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.9-clasify_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:49:28 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/25 07:39:32 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	classify_cmd(char *value)
{
	if (ft_strcmp(value, "echo") == 0 || ft_strcmp(value, "cd") == 0
		|| ft_strcmp(value, "pwd") == 0 || ft_strcmp(value, "export") == 0
		|| ft_strcmp(value, "unset") == 0 || ft_strcmp(value, "env") == 0
		|| ft_strcmp(value, "exit") == 0)
		return (TOKEN_BUILTIN);
	return (TOKEN_ERROR);
}

static t_token_type	classify_operator(char *value)
{
	if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(value, "&&") == 0)
		return (TOKEN_AND);
	if (ft_strcmp(value, "||") == 0)
		return (TOKEN_OR);
	if (ft_strcmp(value, "(") == 0)
		return (TOKEN_LPAREN);
	if (ft_strcmp(value, ")") == 0)
		return (TOKEN_RPAREN);
	return (TOKEN_ERROR);
}

static t_token_type	classify_variable(char *value)
{
	if (ft_isdigit(value[0]) && value[1] == '\0')
		return (TOKEN_EXIT_STATUS);
	if (value[0] == '$')
		return (TOKEN_ENV_VAR);
	return (TOKEN_ERROR);
}

static t_token_type	classify_string(char *value)
{
	if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		return (TOKEN_DOUBLE_QUOTE);
	return (TOKEN_ERROR);
}

t_token_type	clasify_token(char *value)
{
	int	token_type;

	token_type = classify_cmd(value);
	if (token_type != TOKEN_ERROR)
		return (TOKEN_BUILTIN);
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
		return (TOKEN_WORD);
	return (TOKEN_ERROR);
}
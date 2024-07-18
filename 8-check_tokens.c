/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8-check_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:24:43 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/18 12:25:54 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Checks if the given token type is a word token.
 * Returns 1 if it is, 0 otherwise.
 */
int is_word_token(t_token_type type) 
{
    return (type == TOKEN_WORD || type == TOKEN_SINGLE_QUOTE || type == TOKEN_DOUBLE_QUOTE ||
           type == TOKEN_ENV_VAR || type == TOKEN_EXIT_STATUS || type == TOKEN_WILDCARD);
}

/* 
 * Checks if the given token type is a redirection token.
 * Returns 1 if it is, 0 otherwise.
 */
int is_redirection_token(t_token_type type) 
{
    return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || 
           type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

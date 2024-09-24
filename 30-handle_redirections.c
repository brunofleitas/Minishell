/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30-handle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 02:49:56 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/24 00:33:08 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles redirections for a command.
 *
 * This function processes all redirection nodes associated with a command, 
 * including output redirections (both overwrite and append), input 
 * redirections, and heredocs. It calls the appropriate redirection handler 
 * based on the redirection type. If any redirection fails, it restores the 
 * standard I/O and exits with an error.
 *
 * @param redir_node Pointer to the redirection node in the AST.
 * @param ma Pointer to the structure containing metadata, including I/O state.
 * @return 1 on success, 0 on failure (with an exit).
 */
int	handle_redirections(t_astnode *redir_node, t_ma *ma)
{
	while (redir_node != NULL)
	{
		if ((redir_node->u_data.s_redirection.type == TOKEN_REDIR_OUT && \
			!redirect_output(redir_node->u_data.s_redirection.file, 1, ma))
			|| (redir_node->u_data.s_redirection.type == TOKEN_REDIR_APPEND && \
			!redirect_output_append(redir_node->u_data.s_redirection.file, 1,
					ma)) || (redir_node->u_data.s_redirection.type == \
			TOKEN_REDIR_IN
				&& !redirect_input(redir_node->u_data.s_redirection.file, ma))
			|| (redir_node->u_data.s_redirection.type == TOKEN_HEREDOC
				&& !handle_heredoc(redir_node->u_data.s_redirection.file, ma)))
		{
			restore_io(ma);
			exit_or_setexit(1, 0, ma);
			return (0);
		}
		redir_node = redir_node->u_data.s_redirection.next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-builtins_with_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:20:11 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/25 01:31:01 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_add_newline(t_astnode *node)
{
	if (node->data.simple_command.word_count > 1
		&& !strcmp(node->data.simple_command.words->data.word.value[1], "-n"))
		return (0);
	return (1);
}

static char	*join_words(t_astnode *node, t_ntc **first_node, int i)
{
	char	*result;
	char	*temp;

	result = ft_strdup("", first_node);
	while (i < node->data.simple_command.word_count)
	{
		temp = ft_strjoin(result, node->data.simple_command.words[i],
				first_node);
		free(result);
		result = temp;
		if (i < node->data.simple_command.word_count - 1)
		{
			temp = ft_strjoin(result, " ", first_node);
			free(result);
			result = temp;
		}
		i++;
	}
	return (result);
}

char	*builtin_echo(t_astnode *node, t_ntc **first_node)
{
	int		newline;
	int		i;
	char	*result;
	char	*temp;

	newline = should_add_newline(node);
	if (newline)
		i = 1;
	else
		i = 2;
	result = join_words(node, first_node, i);
	if (newline)
	{
		temp = ft_strjoin(result, "\n", first_node);
		free(result);
		result = temp;
	}
	return (result);
}

char	*builtin_pwd(t_ntc **first_node)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strdup_g_c(cwd, first_node));
	else
		ft_printf("getcwd() error");
	return (NULL);
}

char	*builtin_env(char **env, t_ntc **first_node)
{
	int		i;
	size_t	total_length;
	char	*result;
	char	*temp;

	i = 0;
	total_length = 0;
	while (env[i] != NULL)
	{
		total_length += ft_strlen(env[i]) + 1;
		i++;
	}
	result = g_c(first_node, (total_length + 1) * sizeof(char *))->data;
	if (!result)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		ft_strlcat(result, env[i], total_length + 1);
		ft_strlcat(result, "\n", total_length + 1);
		i++;
	}
	return (result);
}

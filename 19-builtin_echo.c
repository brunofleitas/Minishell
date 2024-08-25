/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19-builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:50:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/25 08:26:14 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_add_newline(char **args, int word_count)
{
	if (word_count > 1 && !(ft_strncmp(args[1], "-n", 2)))
		return (0);
	return (1);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*join_words(char **args, t_ntc **first_node, int i, int word_count)
{
	char	*result;
	char	*temp;
	char	*actual_arg;

	result = ft_strdup_g_c("", first_node);
	while (i < word_count)
	{
		actual_arg = ft_strdup_g_c(args[i], first_node);
		temp = ft_strjoin_g_c(result, actual_arg, first_node);
		result = temp;
		if ((i < word_count - 1) && (!ft_isnum(args[i])))
		{
			temp = ft_strjoin_g_c(result, " ", first_node);
			result = temp;
		}
		i++;
	}
	return (result);
}

int	has_a_redirection_output(char *result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		if (result[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_echo(char **args, int word_count, t_ma *ma)
{
	int		newline;
	int		i;
	char	*result;
	char	*temp;

	newline = should_add_newline(args, word_count);
	if (newline)
		i = 1;
	else
		i = 2;
	result = join_words(args, &(ma->first_node), i, word_count);
	if (newline)
	{
		temp = ft_strjoin_g_c(result, "\n", &(ma->first_node));
		result = temp;
	}
	if (result)
	{
		printf("%s", result);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

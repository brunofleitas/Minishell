/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   50-AST_execute_ext_cmd_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 00:39:59 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:43:26 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

char	*get_n_token(const char **s, char c, t_ntc **first_node)
{
	const char	*start;

	while (**s && **s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	return (ft_substr_g_c(start, 0, *s - start, first_node));
}

char	**ft_split(char const *s, char c, t_ntc **first_node)
{
	int		i;
	int		words;
	char	**split;

	i = 0;
	words = word_count(s, c);
	split = (char **)(g_c(first_node, sizeof(char *) * (words + 1))->data);
	if (!s || !split)
		return (NULL);
	while (i < words)
		split[i++] = get_n_token(&s, c, first_node);
	split[i] = NULL;
	return (split);
}

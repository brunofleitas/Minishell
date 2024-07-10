/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:03:22 by bfleitas          #+#    #+#             */
/*   Updated: 2024/07/10 02:40:35 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words_tokens(char const *s, char c)
{
	int	counter;
	int	i;

	i = 0;
	if (*s == '\0')
		return (0);
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
				i++;
			counter++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
			counter++;
		}
		else if (s[i] != c && (i == 0 || s[i - 1] == c))
			counter++;
		i++;
	}
	return (counter);
}

static char	**ft_split_tokens(char const *s, char c)
{
	char	**split;
	int		word_length;
	int		i;

	i = 0;
	split = (char **)malloc((count_words_tokens(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (*s == '"')
			{
				s++;
				word_length = 0;
				while (s[word_length] != '"' && s[word_length])
					word_length++;
				split[i++] = ft_substr(s, 0, word_length);
				s += word_length + 1;
			}
			else if (*s == '\'')
			{
				s++;
				word_length = 0;
				while (s[word_length] != '\'' && s[word_length])
					word_length++;
				split[i++] = ft_substr(s, 0, word_length);
				s += word_length + 1;
			}
			else
			{
				if (!ft_strchr(s, c))
					word_length = ft_strlen(s);
				else
					word_length = (int)(ft_strchr(s, c) - s);
				split[i++] = ft_substr(s, 0, word_length);
				s += word_length;
			}
		}
	}
	split[i] = NULL;
	return (split);
}

void	lexer(char *input)
{
	t_word *tokens[1024];
	char **split;
	int i;

	i = 0;
	split = ft_split_tokens(input, ' ');
	while (split[i])
	{
		tokens[i] = malloc(sizeof(t_word));
		tokens[i]->value = split[i];
		// tokens[i]->key = get_key(tokens[i]->value);
		printf("%s\n", tokens[i]->value);
		i++;
	}
	free(split);
}
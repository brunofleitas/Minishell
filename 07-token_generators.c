/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07-token_generators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 06:18:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/29 21:32:07 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_quotes(const char **s, char ***split, int *i, t_ma *ma)
{
	char	quote;
	char	*result;

	quote = **s;
	(*s)++;
	result = ft_strdup_g_c("", &(ma->first_node));
	append_char(quote, &result, ma);
	handle_quote_content(s, &result, quote, ma);
	handle_newline_if_needed(s, &result, ma);
	append_char(quote, &result, ma);
	(*split)[(*i)++] = result;
	(*s)++;
}

void	generate_double_operators(const char **s, char ***split, int *i,
		t_ma *ma)
{
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, 2, &(ma->first_node));
	*s += 2;
}

void	generate_single_operators_and_specials(const char **s,
		char ***split, int *i, t_ma *ma)
{
	int		len;
	char	*temp;
	char	*env_value;

	len = 1;
	if (**s == '$' && *(*s + 1) == '?')
	{
		(*split)[(*i)++] = ft_itoa_g_c(ma->last_exit_status, &(ma->first_node));
		(*s) += 1;
	}
	else if (**s == '$' && ft_isalnum(*(*s + 1)))
	{
		while ((*s)[len] && (ft_isalnum((*s)[len]) || (*s)[len] == '_'))
			len++;
		temp = ft_substr_g_c(*s + 1, 0, len - 1, &(ma->first_node));
		env_value = get_env(temp, ma->env->var);
		if (env_value)
			(*split)[(*i)++] = ft_strdup_g_c(env_value, &(ma->first_node));
	}
	else
	{
		(*split)[(*i)++] = ft_substr_g_c(*s, 0, 1, &(ma->first_node));
	}
	*s += len;
}

static char	*ft_strremove_quotes(const char *str, t_ntc **first_node)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
	{
		return (NULL);
	}
	result = g_c(first_node, sizeof(char) * (strlen(str) + 1))->data;
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' &&  str[i] != '"')
		{
			result[j++] = str[i++];
			// i++;
		}
		else 
		{
			if (str[i] == '"')
			{
				i++;
				while (str[i] != '"')
					result[j++] = str [i++];
				if (str[i])
					i++;
			}
			else if (str[i] == '\'')
			{
				i++;
				while (str[i] != '\'')
					result[j++] = str [i++];
				if (str[i])
					i++;
			}
		
		}
		// i++;
	}
	result[j] = '\0';
	return (result);
}

void	generate_regular_tkns(const char **s, char ***split, int *i,
		t_ma *ma)
{
	int		word_length;
	char	*temp;
	char	*trimmed;
	//char	*result;

	word_length = 0;
	while ((*s)[word_length])
	{
		if ((*s)[word_length] == '"') 
		{
			word_length++;
			while (!((*s)[word_length] == '"'))
				word_length++;
			word_length++;
		}
		else if ((*s)[word_length] == '\'')
		{
			word_length++;
			while (!((*s)[word_length] == '\''))
				word_length++;
			word_length++;
		}
		else if (!ft_strchr(" ><&()|$", (*s)[word_length]))
			word_length++;
		else
			break;
	}
	temp = ft_substr_g_c(*s, 0, word_length, &(ma->first_node));
	trimmed = ft_strremove_quotes(temp, &(ma->first_node));
	// result = ft_strremove_char(trimmed, '\"', &(ma->first_node));
	//result = ft_strtrim(result, " ", &(ma->first_node));
	(*split)[(*i)++] = trimmed;
	*s += word_length;
}

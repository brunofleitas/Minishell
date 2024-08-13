/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-split_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:14:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/13 14:48:00 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env(char *name, char **env)
{
	int		i;
	int		name_len;

	if (!name || !env)
		return (NULL);
	name_len = strlen(name);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (&env[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

static void	handle_env_var(const char **s, char **result, int *result_len, char **env)
{
	char	var_name[1024];
	int		var_name_len;
	char	*env_value;

	var_name_len = 0;
	(*s)++;
	while (ft_isalnum(**s) || **s == '_')
		var_name[var_name_len++] = *(*s)++;
	var_name[var_name_len] = '\0';
	env_value = get_env(var_name, env);
	if (env_value)
	{
		*result = realloc(*result, *result_len + strlen(env_value) + 1);
		if (*result)
		{
			strcpy(*result + *result_len, env_value);
			*result_len += strlen(env_value);
		}
	}
}

static void	append_char(const char **s, char **result, int *result_len)
{
	*result = realloc(*result, *result_len + 2);
	if (*result)
	{
		(*result)[(*result_len)++] = **s;
		(*result)[*result_len] = '\0';
	}
	(*s)++;
}

static void	generate_quotes(const char **s, char ***split, int *i, t_ntc **first_node, char **env)
{
	char	quote;
	char	*result;
	int		result_len;

(void)first_node;
	quote = **s;
	(*s)++;
	result = strdup("");
	result_len = 0;
	while (**s && **s != quote)
	{
		if (quote == '"' && **s == '$')
			handle_env_var(s, &result, &result_len, env);
		else
			append_char(s, &result, &result_len);
	}
	(*split)[(*i)++] = result;
	if (**s == quote)
		(*s)++;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a double operator (e.g., '>>', '<<', '&&', '||') from 
	the input string into the tkns array. Advances the input string by 2 
	positions to skip the operator.
*/
static void	generate_double_operators(const char **s, char ***split, int *i, \
															t_ntc **first_node)
{
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, 2, first_node);
	*s += 2;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a single operator or special character (including '$?') 
	from the input string into the tkns array. The length of the substring 
	depends on the specific operator or special character.
    Advances the input string by the length of the extracted substring.
*/


static void	generate_single_operators_and_specials(const char **s,
		char ***split, int *i, t_ntc **first_node, t_ma *ma)
{
	int	len;
	char	*temp;
	char	*env_value;

	len = 1;
	if (**s == '$' && *(*s + 1) == '?')
	{
		(*split)[(*i)++] = ft_substr_g_c(ft_itoa_gb(ma->last_exit_status, first_node), 0, ft_strlen(ft_itoa_gb(ma->last_exit_status, first_node)), first_node);
	}
	else if (**s == '$')
	{
		while ((*s)[len] && (ft_isalnum((*s)[len]) || (*s)[len] == '_'))
			len++;
		temp = ft_substr_g_c(*s + 1, 0, len - 1, first_node);
		env_value = get_env(temp, ma->env->var);
		if (env_value)
			(*split)[(*i)++] = ft_strdup_g_c(env_value, first_node);
		else
			(*split)[(*i)++] = ft_strdup_g_c("", first_node);
	}
	else
	{
		(*split)[(*i)++] = ft_substr_g_c(*s, 0, 1, first_node);
	}
	*s += len;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a regular token (any sequence of characters not 
	matching the specified operators or special characters) from the input 
	string into the tkns array. Calculates the length of the token by finding 
	the first occurrence of an operator or special character. Advances the 
	input string by the length of the extracted token.
*/
static void	generate_regular_tkns(const char **s, char ***split, int *i, \
																t_ntc **first_node)
{
	int	word_length;

	word_length = 0;
	while ((*s)[word_length] && !strchr(" ><&()|$", (*s)[word_length]))
		word_length++;
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, word_length, first_node);
	*s += word_length;
}

/*
  Parameters:
	s: Input string to be split into tkns.
	c: Character used to determine token boundaries.
  Return value:
	A pointer to an array of strings, each representing a token from the input
	string.
	Returns NULL if the input string or the allocated memory cannot be processed
  Description:
	Splits the input string into tkns based on the specified delimiter
	character.
	Handles various cases including quotes, double operators, single operators,
	and regular tkns. Allocates memory for the resulting array of tkns and
	initializes it accordingly. The last element of the array is set to NULL
	to indicate the end.
*/
char	**ft_split_tkns(char const *s, char c, t_ntc **first_node, t_ma *ma)
{
	char	**split;
	int		i;

	i = 0;
	split = g_c(first_node, (count_w_tks(s, c) + 1) * sizeof(char *))->data;
	if (!s || !split)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else if (*s == '"' || *s == '\'')
			generate_quotes(&s, &split, &i, first_node, ma->env->var);
		else if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s
					+ 1) == '<') || (*s == '&' && *(s + 1) == '&') || (*s == '|'
				&& *(s + 1) == '|'))
			generate_double_operators(&s, &split, &i, first_node);
		else if (*s == '>' || *s == '<' || *s == '(' || *s == ')' || *s == '|'
			|| (*s == '$' && *(s + 1) == '?') || *s == '$')
			generate_single_operators_and_specials(&s, &split, &i, first_node, ma);
		else
			generate_regular_tkns(&s, &split, &i, first_node);
	}
	split[i] = NULL;
	return (split);
}
// f_node is an alias for first_node but I had to shorten it otherwise the funtion would have been more than 25 lines long.

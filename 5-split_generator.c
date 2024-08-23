/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-split_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:14:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/20 12:54:13 by bfleitas         ###   ########.fr       */
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

static void	handle_env_var(const char **s, char **result, int *result_len, t_ma *ma)
{
	char	var_name[1024];
	int		var_name_len;
	char	*env_value;

	var_name_len = 0;
	(*s)++;
	while (ft_isalnum(**s) || **s == '_')
		var_name[var_name_len++] = *(*s)++;
	var_name[var_name_len] = '\0';
	env_value = get_env(var_name, (ma->env->var));
	if (env_value)
	{
		*result = ft_realloc_g_c(&(ma->first_node), *result, (*result_len + strlen(env_value) + 1));
		if (*result)
		{
			strcpy(*result + *result_len, env_value);
			*result_len += strlen(env_value);
		}
	}
}

static void	append_char(char s, char **result, int *result_len, t_ma *ma)
{
	*result = ft_realloc_g_c(&(ma->first_node), *result, *result_len + 2);
	if (*result)
	{
		(*result)[(*result_len)++] = s;
		(*result)[*result_len] = '\0';
	}
}

static void	generate_quotes(const char **s, char ***split, int *i, t_ma *ma)
{
	char	quote;
	char	*result;
	int		result_len;
	char	*exit_value;

	quote = **s;
	(*s)++;
	result = ft_strdup_g_c("", &(ma->first_node));
	result_len = 0;
	//printf("Char: %c\n", **s);
	append_char(quote, &result, &result_len, ma);
	while (**s && **s != quote)
	{
		if (quote == '"' && **s == '$' && ft_isalnum(*(*s + 1)))
			handle_env_var(s, &result, &result_len, ma);
		else if (quote == '"' && **s == '$' && (*(*s + 1) == '?'))
		{
			exit_value = ft_substr_g_c(ft_itoa_g_c(ma->last_exit_status, &(ma->first_node)), 0, ft_strlen(ft_itoa_g_c(ma->last_exit_status, &(ma->first_node))), &(ma->first_node));
			while (*exit_value)
				append_char(*exit_value++, &result, &result_len, ma);
			(*s) += 2;
		}
		else
		{
			//printf("Char: %c\n", **s);
			append_char(**s, &result, &result_len, ma); // Corrected: pass a single char
			(*s)++;
		}
	}
	if (((*(*s + 1)) && (*(*s + 1)) == '$') && ((*(*s + 2)) || (*(*s + 2) == ' ')))
    {
        append_char('\n', &result, &result_len, ma);
		(*s)++;
    }
	if (((*(*s + 1)) && (*(*s + 1)) == '$') && (*(*s + 2) == '\0'))
	{
		append_char('\n', &result, &result_len, ma);
		(*s)++;
	}
	//printf("Char: %c\n", **s);
	append_char(quote, &result, &result_len, ma);
	//printf("Result: %s\n", result);
	(*split)[(*i)++] = result;
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
															t_ma *ma)
{
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, 2, &(ma->first_node));
	*s += 2;
}


/**
 * Generates single operators and special characters from the input string (including '$?') 
 * from the input string into the tkns array. The length of the substring 
 * depends on the specific operator or special character.
 * Advances the input string by the length of the extracted substring. 
 * @param s The input string.
 * @param split The array to store the generated strings.
 * @param i The index of the current element in the split array.
 * @param ma The main structure containing relevant data.
 */
static void	generate_single_operators_and_specials(const char **s,
		char ***split, int *i, t_ma *ma)
{
	int	len;
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

char *ft_strremove_char(const char *str, char char_to_remove, t_ntc **first_node)
{
    char *result;
    int i;
    int j;

    if (!str) {
        return NULL;
    }
    result = g_c(first_node, sizeof(char) * (strlen(str) + 1))->data;
    if (!result) {
        return NULL;
    }
    i = 0;
    j = 0;
    while (str[i] != '\0') {
        if (str[i] != char_to_remove) {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';
    return result;
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
																t_ma *ma)
{
	int	word_length;
	char	*temp;
	char	*trimmed;
	char *result;

	word_length = 0;
	while ((*s)[word_length] && !strchr(" ><&()|$", (*s)[word_length]))
	{
		if (ft_isdigit((*s)[word_length]) && ((*s)[word_length + 1] && (*s)[word_length + 1] == '>') && ((*s)[word_length + 2] && (*s)[word_length + 2] == '>'))
			break ;
		else if (ft_isdigit((*s)[word_length]) && ((*s)[word_length + 1] && (*s)[word_length + 1] == '>'))
			break ;
		else
			word_length++;
	}
	temp = ft_substr_g_c(*s, 0, word_length, &(ma->first_node));
	trimmed = ft_strremove_char(temp, '\'', &(ma->first_node));
	result = ft_strremove_char(trimmed, '\"', &(ma->first_node));
	result = ft_strtrim(result, " ", &(ma->first_node));
	(*split)[(*i)++] = result;
	*s += word_length;
}

// static void handle_redirection(const char **s, char ***split, int *i, t_ntc **first_node)
// {
//     if (ft_isdigit((*s)[0]) && (((*s)[1] == '>') || ((*s)[1] == '>' && (*s)[2] == '>')))
// 	{
//         char *token;
//         int length;
        
//         if ((*s)[1] == '>' && (*s)[2] == '>')
//             length = 3;
//         else
//             length = 2;
//         token = ft_substr_g_c(*s, 0, length, first_node);
//         (*split)[(*i)++] = token;
//         *s += length;
//     }
// }

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
/**
 * Splits a string into tokens based on a given delimiter.
 *
 * @param c The delimiter character.
 * @param ma The memory allocator structure.
 * @return An array of strings representing the tokens.
 */
char **ft_split_tkns(char c, t_ma *ma)
{
	char **split;
	int i;
	const char *s;

	s = (const char*)ma->input;
	i = 0;
	//printf("Tkns: %d\n", count_tks(s, c));
	split = g_c(&(ma->first_node), (count_tks(s, c) + 1) * sizeof(char *))->data;
	if (!s || !split)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		// else if (ft_isdigit(*s))
        //     handle_redirection(&s, &split, &i, first_node);
		else if (*s == '"' || *s == '\'')
			generate_quotes(&s, &split, &i, ma);
		else if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s
					+ 1) == '<') || (*s == '&' && *(s + 1) == '&') || (*s == '|'
				&& *(s + 1) == '|'))
			generate_double_operators(&s, &split, &i, ma);
		else if (*s == '>' || *s == '<' || *s == '(' || *s == ')' || *s == '|'
			|| (*s == '$' && *(s + 1) == '?') || *s == '$')
			generate_single_operators_and_specials(&s, &split, &i, ma);			
		else
			generate_regular_tkns(&s, &split, &i, ma);
	}
	split[i] = NULL;
	return (split);
}
// f_node is an alias for first_node but I had to shorten it otherwise the funtion would have been more than 25 lines long.

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-generate_regular.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:09:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:00:21 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Generates regular tokens with potential environment variable expansion.
 *
 * This function processes a regular token, handles any environment variable 
 * expansion within the token, and removes quotes if necessary. The resulting 
 * token is stored in the split array, and the string pointer is advanced 
 * accordingly.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param split Array of strings where the generated tokens are stored.
 * @param i Pointer to the current index in the split array.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and state management.
 */
void	generate_regular_tkns(const char **s, char ***split, int *i, t_ma *ma)
{
	int		word_length;
	char	*temp;
	char	*trimmed;
	char	*result;

	word_length = get_word_length(*s);
	temp = ft_substr_g_c(*s, 0, word_length, &(ma->first_node));
	if (ft_strchr(temp, '=') && ft_strchr(temp, '"') && ft_strchr(temp, '$'))
		result = handle_env_in_var(temp, ma);
	else
		result = process_dollar_expansion(s, temp, word_length, ma);
	trimmed = ft_strremove_quotes(result, &(ma->first_node));
	(*split)[(*i)++] = trimmed;
	*s += word_length;
}

/**
 * @brief Gets the length of a word, accounting for quotes.
 *
 * This function calculates the length of a word in a string, considering 
 * quoted sections (both single and double quotes) and stopping at special 
 * characters (e.g., `>`, `<`, `&`, `|`, `$`). Quoted sections are skipped 
 * without being broken.
 *
 * @param s Pointer to the current position in the string.
 * @return The length of the word.
 */
int	get_word_length(const char *s)
{
	int	word_length;

	word_length = 0;
	while (s[word_length])
	{
		if (s[word_length] == '"')
		{
			word_length++;
			while (s[word_length] != '"')
				word_length++;
			word_length++;
		}
		else if (s[word_length] == '\'')
		{
			word_length++;
			while (s[word_length] != '\'')
				word_length++;
			word_length++;
		}
		else if (!ft_strchr("' ><&()|$", s[word_length]))
			word_length++;
		else
			break ;
	}
	return (word_length);
}

/**
 * @brief Handles environment variable expansion within a variable assignment.
 *
 * This function processes a string representing a variable assignment that 
 * contains environment variables (denoted by `$`). It expands the variables 
 * and constructs the resulting string with the expanded values.
 *
 * @param temp The input string containing the variable assignment and 
 *             potential environment variables.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and environment management.
 * @return The resulting string with expanded environment variables.
 */
char	*handle_env_in_var(char *temp, t_ma *ma)
{
	char	*result;
	int		i;

	result = ft_strdup_g_c("", &(ma->first_node));
	i = 0;
	while (temp[i] != '=')
		append_char(temp[i++], &result, ma);
	while (temp[i])
	{
		if (temp[i] == '$')
			append_env_value(temp, &i, &result, ma);
		else
			append_char(temp[i++], &result, ma);
	}
	return (result);
}

/**
 * @brief Processes environment variable expansion within a word.
 *
 * This function handles the expansion of environment variables within a 
 * word, if a dollar sign (`$`) is detected followed by an alphanumeric 
 * character or underscore. It replaces the variable with its value and 
 * concatenates the remaining part of the word, if any.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param temp The word before expansion.
 * @param word_length The length of the word before encountering the dollar sign.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and environment management.
 * @return The word with the environment variable expanded, or the original 
 *         word if no expansion is needed.
 */
char	*process_dollar_expansion(const char **s, char *temp,
	int word_length, t_ma *ma)
{
	int		len_var;
	char	*env_value;
	char	*ad_word;
	char	*result;

	result = temp;
	len_var = 1;
	if (((*s)[word_length] == '$') && (ft_isalnum((*s)[word_length + 1])
		|| (*s)[word_length + 1] == '_'))
	{
		while ((*s)[word_length + len_var]
			&& (ft_isalnum((*s)[word_length + len_var])
			|| (*s)[word_length + len_var] == '_'))
			len_var++;
		env_value = get_env_var_value(*s, word_length, len_var, ma);
		if (env_value)
		{
			result = ft_strjoin_g_c(result, env_value, &(ma->first_node));
			ad_word = append_remaining_word(*s, word_length, len_var, ma);
			result = ft_strjoin_g_c(result, ad_word, &(ma->first_node));
		}
	}
	return (result);
}

/**
 * @brief Removes single and double quotes from a string.
 *
 * This function processes a string and removes any single (`'`) or double 
 * (`"`) quotes found within it. If double quotes are encountered, special 
 * handling may apply. The resulting string is stored in a memory block 
 * managed by the garbage collector.
 *
 * @param str The input string from which quotes are to be removed.
 * @param first_node Pointer to the first node of the memory allocation 
 *                   chain for garbage collection.
 * @return A new string with quotes removed, or NULL if memory allocation fails.
 */
char	*ft_strremove_quotes(const char *str, t_ntc **first_node)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = g_c(first_node, sizeof(char) * (strlen(str) + 1))->data;
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '"')
			result[j++] = str[i++];
		else if (str[i] == '"')
			handle_dq(str, result, &i, &j);
		else if (str[i] == '\'')
			handle_sq(str, result, &i, &j);
	}
	result[j] = '\0';
	return (result);
}

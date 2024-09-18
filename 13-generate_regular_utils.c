/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-generate_regular_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:12:34 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:01:57 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends the value of an environment variable to the result string.
 *
 * This function extracts an environment variable name from the input string, 
 * retrieves its value, and appends the value to the result string. It advances 
 * the input string pointer accordingly.
 *
 * @param temp The input string containing the environment variable reference.
 * @param i Pointer to the current index in the input string.
 * @param result Pointer to the result string where the environment value 
 *               will be appended.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and environment variables.
 */
void	append_env_value(const char *temp, int *i, char **result, t_ma *ma)
{
	char	*var_name;
	char	*env_value;
	int		len_var;

	len_var = 1;
	if (ft_isalnum(temp[*i + 1]) || temp[*i + 1] == '_')
	{
		while (temp[*i + len_var] && (ft_isalnum(temp[*i + len_var])
				|| temp[*i + len_var] == '_'))
			len_var++;
		var_name = ft_substr_g_c(temp, *i + 1, len_var - 1, &(ma->first_node));
		env_value = get_env(var_name, ma->env->var);
		if (env_value)
			*result = ft_strjoin_g_c(*result, env_value, &(ma->first_node));
		*i += len_var;
	}
}

/**
 * @brief Retrieves the value of an environment variable from a string.
 *
 * This function extracts an environment variable name from a portion of the 
 * input string, retrieves its value from the environment, and returns it.
 *
 * @param s The input string containing the environment variable reference.
 * @param word_length The length of the word before the environment variable 
 * 					  starts.
 * @param len_var The length of the environment variable name.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and environment variables.
 * @return The value of the environment variable, or NULL if not found.
 */
char	*get_env_var_value(const char *s, int word_length, int len_var,
	t_ma *ma)
{
	char	*temp;
	char	*env_value;

	temp = ft_substr_g_c(s + word_length + 1, 0, len_var - 1,
			&(ma->first_node));
	env_value = get_env(temp, ma->env->var);
	return (env_value);
}

/**
 * @brief Appends the remaining part of a word after an environment variable.
 *
 * This function extracts and returns the portion of the input string that 
 * follows an environment variable, up until a special character or the end 
 * of the word.
 *
 * @param s The input string containing the word.
 * @param word_length The length of the word before the environment variable.
 * @param len_var The length of the environment variable name.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and state management.
 * @return The remaining part of the word after the environment variable.
 */
char	*append_remaining_word(const char *s, int word_length, int len_var,
	t_ma *ma)
{
	int		len_after;
	char	*ad_word;

	len_after = 0;
	while (s[word_length + len_var + len_after]
		&& !ft_strchr(" ><&()|$", s[word_length + len_var + len_after]))
		len_after++;
	ad_word = ft_substr_g_c(s, word_length + len_var, len_after,
			&(ma->first_node));
	return (ad_word);
}

/**
 * @brief Handles content inside double quotes during string processing.
 *
 * This function processes the content inside double quotes in the input 
 * string and copies it to the result string, excluding the double quotes 
 * themselves. It advances the input and result string indices accordingly.
 *
 * @param str The input string being processed.
 * @param result The result string where the content inside double quotes 
 *               is copied.
 * @param i Pointer to the current index of the input string.
 * @param j Pointer to the current index of the result string.
 */
void	handle_dq(const char *str, char *result, int *i, int *j)
{
	(*i)++;
	while (str[*i] != '"')
		result[(*j)++] = str[(*i)++];
	if (str[*i])
		(*i)++;
}

/**
 * @brief Handles content inside single quotes during string processing.
 *
 * This function processes the content inside single quotes in the input 
 * string and copies it to the result string, excluding the single quotes 
 * themselves. It advances the input and result string indices accordingly.
 *
 * @param str The input string being processed.
 * @param result The result string where the content inside single quotes 
 *               is copied.
 * @param i Pointer to the current index of the input string.
 * @param j Pointer to the current index of the result string.
 */
void	handle_sq(const char *str, char *result, int *i, int *j)
{
	(*i)++;
	while (str[*i] != '\'')
		result[(*j)++] = str[(*i)++];
	if (str[*i])
		(*i)++;
}

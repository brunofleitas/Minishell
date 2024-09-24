/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09-generate_quotes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:51:35 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/24 11:07:55 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles special characters during string parsing.
 *
 * This function processes special characters in a string based on the 
 * context of the provided quote. It handles environment variable expansion 
 * and special cases like the exit status `$?` when inside double quotes.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param result Pointer to the result string where processed characters 
 *               are appended.
 * @param quote Character representing the current quote context ('"' or '\'').
 * @param ma Pointer to the structure containing metadata like last exit 
 *           status and memory allocation nodes.
 * @return 1 if a special character was handled, 0 otherwise.
 */
int	handle_special(const char **s, char **result, char quote, t_ma *ma)
{
	char	*exit_value;

	if (quote == '"' && **s == '$' && ft_isalnum(*(*s + 1)))
	{
		handle_env_var(s, result, ma);
		return (1);
	}
	else if (quote == '"' && **s == '$' && (*(*s + 1) == '?'))
	{
		exit_value = ft_itoa_g_c(ma->last_exit_status, &(ma->first_node));
		while (*exit_value)
			append_char(*exit_value++, result, ma);
		(*s) += 2;
		return (1);
	}
	return (0);
}

/**
 * @brief Handles special cases of double quotes during string parsing.
 *
 * This function processes specific cases where consecutive double quotes 
 * or a double quote followed by an equals sign are encountered in a string.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param result Pointer to the result string where processed characters 
 *               are appended.
 * @param quote Character representing the double quote context ('"').
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and state management.
 * @return 1 if a double quote case was handled, 0 otherwise.
 */
int	handle_double_q(const char **s, char **result, char quote, t_ma *ma)
{
	if (**s == quote && *(*s + 1) == quote)
	{
		(*s) += 2;
		return (1);
	}
	if (**s == quote && *(*s + 1) == '=')
	{
		(*s)++;
		append_char(*(*s)++, result, ma);
		return (1);
	}
	return (0);
}

/**
 * @brief Handles environment variable expansion in a string.
 *
 * This function processes and expands environment variables within a string. 
 * It reads the variable name after a `$` symbol and replaces it with the 
 * corresponding value from the environment, if found.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param result Pointer to the result string where the expanded value 
 *               is appended.
 * @param ma Pointer to the structure containing the environment and 
 *           memory allocation nodes.
 */
void	handle_env_var(const char **s, char **result, t_ma *ma)
{
	char	var_name[1024];
	int		var_name_len;
	char	*env_value;
	int		result_len;

	result_len = ft_strlen(*result);
	var_name_len = 0;
	(*s)++;
	while (ft_isalnum(**s) || **s == '_')
		var_name[var_name_len++] = *(*s)++;
	var_name[var_name_len] = '\0';
	env_value = get_env(var_name, (ma->env->var), ma);
	if (env_value)
	{
		*result = ft_realloc_g_c(&(ma->first_node), *result, (result_len
					+ strlen(env_value) + 1));
		if (*result)
		{
			strcpy(*result + result_len, env_value);
			result_len += strlen(env_value);
		}
	}
	free(env_value);
}

/**
 * @brief Retrieves the value of an environment variable.
 *
 * This function searches for the specified environment variable name in the 
 * provided environment array. If found, it returns the associated value 
 * with extra spaces removed.
 *
 * @param name Name of the environment variable to search for.
 * @param env Array of environment strings where each entry is in the form 
 *            "NAME=VALUE".
 * @return The value of the environment variable, or NULL if not found.
 */
char	*get_env(char *name, char **env, t_ma *ma)
{
	int		i;
	int		name_len;
	char	*env_value;

	if (!name || !env)
		return (NULL);
	name_len = strlen(name);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			env_value = &env[i][name_len + 1];
			return (remove_extra_spaces(env_value, ma));
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief Removes consecutive spaces from a string.
 *
 * This function processes a string and removes consecutive spaces, leaving 
 * only a single space between words. Leading and trailing spaces are also 
 * removed.
 *
 * @param str The input string to process.
 * @return A new string with extra spaces removed, or NULL if memory 
 *         allocation fails.
 */
char	*remove_extra_spaces(char *str, t_ma *ma)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	(void)ma;
	i = 0;
	j = 0;
	len = strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != ' ' || (i > 0 && str[i - 1] != ' '))
			result[j++] = str[i];
		i++;
	}
	if (j > 0 && result[j - 1] == ' ')
		j--;
	result[j] = '\0';
	return (result);
}

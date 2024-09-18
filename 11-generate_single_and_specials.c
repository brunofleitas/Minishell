/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-generate_single_and_specials.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:08:11 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 00:36:51 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Generates single character operators and special cases.
 *
 * This function processes the input string to handle special cases like 
 * the `$?` operator, environment variables, and other single character 
 * operators. It stores the results in the split array and advances the 
 * string pointer accordingly.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param split Array of strings where the operators or substrings are stored.
 * @param i Pointer to the current index in the split array.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and state management.
 */
void	generate_single_operators_and_specials(const char **s, char ***split,
		int *i, t_ma *ma)
{
	if (**s == '$' && *(*s + 1) == '?')
	{
		(*split)[(*i)++] = ft_itoa_g_c(ma->last_exit_status, &(ma->first_node));
		(*s) += 2;
		return ;
	}
	if (**s == '$' && (ft_isalnum(*(*s + 1)) || *(*s + 1) == '_'))
		handle_env_vari(s, split, i, ma);
	else if (**s == '$')
		handle_regular_substring(s, split, i, ma);
	else
		(*split)[(*i)++] = ft_substr_g_c(*s, 0, 1, &(ma->first_node));
	*s += 1;
}

/**
 * @brief Handles environment variable expansion and concatenation.
 *
 * This function processes an environment variable in the input string, 
 * retrieves its value, and concatenates it with the subsequent word if 
 * applicable. The result is stored in the split array, and the string pointer 
 * is advanced accordingly.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param split Array of strings where the expanded value and concatenated 
 *              result are stored.
 * @param i Pointer to the current index in the split array.
 * @param ma Pointer to the structure containing metadata for environment 
 *           variables and memory management.
 */
void	handle_env_vari(const char **s, char ***split, int *i, t_ma *ma)
{
	int		len;
	int		len_after;
	char	*temp;
	char	*env_value;
	char	*ad_word;

	len = 1;
	while ((*s)[len] && (ft_isalnum((*s)[len]) || (*s)[len] == '_'))
		len++;
	temp = ft_substr_g_c(*s + 1, 0, len - 1, &(ma->first_node));
	env_value = get_env(temp, ma->env->var);
	if (env_value)
	{
		len_after = len;
		while ((*s)[len_after] && !ft_strchr(" ><&()|$", (*s)[len_after]))
			len_after++;
		ad_word = ft_substr_g_c(*s, len, len_after - len, &(ma->first_node));
		(*split)[(*i)++] = ft_strjoin_g_c(env_value, ad_word,
				&(ma->first_node));
		*s += len_after;
	}
	else
		*s += len;
}

/**
 * @brief Handles regular substrings until a special character is encountered.
 *
 * This function extracts a regular substring from the input string, stopping 
 * when a special character (e.g., `>`, `<`, `&`, `|`, `$`) is encountered. 
 * The substring is stored in the split array, and the string pointer is 
 * advanced accordingly.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param split Array of strings where the substring is stored.
 * @param i Pointer to the current index in the split array.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and state management.
 */
void	handle_regular_substring(const char **s, char ***split, int *i,
		t_ma *ma)
{
	int	len;

	len = 1;
	while ((*s)[len] && !ft_strchr(" ><&()|$", (*s)[len]))
		len++;
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, len, &(ma->first_node));
	*s += len;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06-split_generator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:14:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/29 21:18:25 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_char(const char **s, char ***split, int *i, t_ma *ma)
{
	if (**s == '"' || **s == '\'')
		generate_quotes(s, split, i, ma);
	else if ((**s == '>' && *(*s + 1) == '>') || (**s == '<' && *(*s
				+ 1) == '<') || (**s == '&' && *(*s + 1) == '&') || (**s == '|'
			&& *(*s + 1) == '|'))
		generate_double_operators(s, split, i, ma);
	else if (**s == '>' || **s == '<' || **s == '(' || **s == ')' || **s == '|'
		|| (**s == '$' && *(*s + 1) == '?') || **s == '$')
		generate_single_operators_and_specials(s, split, i, ma);
	else
		generate_regular_tkns(s, split, i, ma);
}

char	**ft_split_tkns(char c, t_ma *ma)
{
	char		**split;
	int			i;
	const char	*s;

	s = (const char *)ma->input;
	i = 0;
	split = g_c(&(ma->first_node), (count_tks(s, c) + 1)
			* sizeof(char *))->data;
	if (!s || !split)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
			process_char(&s, &split, &i, ma);
	}
	split[i] = NULL;
	return (split);
}

// char **ft_split_tkns(char c, t_ma *ma)
// {
// 	char **split;
// 	int i;
// 	const char *s;

// 	s = (const char*)ma->input;
// 	i = 0;
// 	split = g_c(&(ma->first_node), (count_tks(s, c) + 1)
//			* sizeof(char *))->data;
// 	if (!s || !split)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s == c)
// 			s++;
// 		else if (*s == '"' || *s == '\'')
// 			generate_quotes(&s, &split, &i, ma);
// 		else if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s+ 1) == '<')
// 			|| (*s == '&' && *(s + 1) == '&') || (*s == '|' && *(s + 1) == '|'))
// 			generate_double_operators(&s, &split, &i, ma);
// 		else if (*s == '>' || *s == '<' || *s == '(' || *s == ')' || *s == '|'
// 			|| (*s == '$' && *(s + 1) == '?') || *s == '$')
// 			generate_single_operators_and_specials(&s, &split, &i, ma);
// 		else
// 			generate_regular_tkns(&s, &split, &i, ma);
// 	}
// 	split[i] = NULL;
// 	return (split);
// }

// static void	generate_quotes(const char **s, char ***split, int *i, t_ma *ma)
// {
// 	char	quote;
// 	char	*result;
// 	int		result_len;
// 	char	*exit_value;
// 	quote = **s;
// 	(*s)++;
// 	result = ft_strdup_g_c("", &(ma->first_node));
// 	result_len = 0;
// 	append_char(quote, &result, &result_len, ma);
// 	while (**s)
// 	{
// 		if (**s == quote && *(*s + 1) == quote)
// 		{
// 			(*s) += 2;
// 			continue ;
// 		}
// 		else if (**s == quote)
// 		{
// 			break ;
// 		}
// 		else if (quote == '"' && **s == '$' && ft_isalnum(*(*s + 1)))
// 		{
// 			handle_env_var(s, &result, &result_len, ma);
// 		}
// 		else if (quote == '"' && **s == '$' && (*(*s + 1) == '?'))
// 		{
// 			exit_value = ft_itoa_g_c(ma->last_exit_status, &(ma->first_node));
// 			while (*exit_value)
// 				append_char(*exit_value++, &result, &result_len, ma);
// 			(*s) += 2;
// 		}
// 		else
// 		{
// 			append_char(**s, &result, &result_len, ma);
// 			(*s)++;
// 		}
// 	}
// 	if (((*(*s + 1)) && (*(*s + 1)) == '$') && ((*(*s + 2)) || (*(*s
//					+ 2) == ' ')))
//     {
//         append_char('\n', &result, &result_len, ma);
// 		(*s)++;
//     }
// 	if (((*(*s + 1)) && (*(*s + 1)) == '$') && (*(*s + 2) == '\0'))
// 	{
// 		append_char('\n', &result, &result_len, ma);
// 		(*s)++;
// 	}
// 	append_char(quote, &result, &result_len, ma);
// 	(*split)[(*i)++] = result;
// 	(*s)++;
// }

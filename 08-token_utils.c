/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8-token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 07:19:53 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/25 07:34:53 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *name, char **env)
{
	int	i;
	int	name_len;

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
	env_value = get_env(var_name, (ma->env->var));
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
}

void	append_char(char s, char **result, t_ma *ma)
{
	int	result_len;

	result_len = ft_strlen(*result);
	*result = ft_realloc_g_c(&(ma->first_node), *result, result_len + 2);
	if (*result)
	{
		(*result)[result_len++] = s;
		(*result)[result_len] = '\0';
	}
}

void	handle_quote_content(const char **s, char **result, char quote,
		t_ma *ma)
{
	char	*exit_value;

	while (**s)
	{
		if (**s == quote && *(*s + 1) == quote)
		{
			(*s) += 2;
			continue ;
		}
		else if (**s == quote)
			break ;
		else if (quote == '"' && **s == '$' && ft_isalnum(*(*s + 1)))
			handle_env_var(s, result, ma);
		else if (quote == '"' && **s == '$' && (*(*s + 1) == '?'))
		{
			exit_value = ft_itoa_g_c(ma->last_exit_status, &(ma->first_node));
			while (*exit_value)
				append_char(*exit_value++, result, ma);
			(*s) += 2;
		}
		else
			append_char(*(*s)++, result, ma);
	}
}

void	handle_newline_if_needed(const char **s, char **result, t_ma *ma)
{
	if (((*(*s + 1)) && (*(*s + 1)) == '$') && ((*(*s + 2)) || (*(*s
					+ 2) == ' ')))
	{
		append_char('\n', result, ma);
		(*s)++;
	}
	if (((*(*s + 1)) && (*(*s + 1)) == '$') && (*(*s + 2) == '\0'))
	{
		append_char('\n', result, ma);
		(*s)++;
	}
}

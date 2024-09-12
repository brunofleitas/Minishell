/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07-token_generators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 06:18:08 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/12 23:54:00 by bfleitas         ###   ########.fr       */
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

void generate_single_operators_and_specials(const char **s,
                                            char ***split, int *i, t_ma *ma)
{
    int len = 1;
    char *temp;
    char *env_value;
    int len_after;
    char *ad_word;

    // Case: Handle special variable $?
    if (**s == '$' && *(*s + 1) == '?')
    {
        (*split)[(*i)++] = ft_itoa_g_c(ma->last_exit_status, &(ma->first_node));
        (*s) += 2; // Move past "$?"
        return;
    }
	len = 1;
    // Case: Handle environment variables starting with $
    if (**s == '$')
    { // Start after the '$'
        if (ft_isalnum(*(*s + 1)) || *(*s + 1) == '_')
        {
            // Find the length of the variable name
            while ((*s)[len] && (ft_isalnum((*s)[len]) || (*s)[len] == '_'))
                len++;
            // Extract variable name
            temp = ft_substr_g_c(*s + 1, 0, len - 1, &(ma->first_node));
            env_value = get_env(temp, ma->env->var);
            if (env_value)
            {
                // If there is something after the variable name, handle it
                len_after = len;
                while ((*s)[len_after] && !ft_strchr(" ><&()|$", (*s)[len_after]))
                    len_after++;
                // Extract the part after the variable name
                ad_word = ft_substr_g_c(*s, len, len_after - len, &(ma->first_node));
				// printf("env_value: %s\n", env_value);
                //printf("%s\n", ft_strjoin_g_c(env_value, ad_word, &(ma->first_node)));
				(*split)[(*i)++] = ft_strjoin_g_c(env_value, ad_word, &(ma->first_node));
                len = len_after;
			}
        }
        else
        {
             while ((*s)[len] && !ft_strchr(" ><&()|$", (*s)[len]))
                    len++;
			// Case: Variable with no alphanumeric characters, treat as plain text
            (*split)[(*i)++] = ft_substr_g_c(*s, 0, len, &(ma->first_node));
        }
    }
    else
    {
        // Case: Handle single operators and specials
        (*split)[(*i)++] = ft_substr_g_c(*s, 0, 1, &(ma->first_node));
    }

    // Move the string pointer forward
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

/* char *expand_vars(char *str, t_ma *ma)
{
	char	*result;
	int		i;
	int		len_var;
	char	*temp;
	char	*env_value;
	int		len_after;
	char	*ad_word;

	i = 0;
	result = ft_strdup_g_c("", &(ma->first_node));
	while (str[i])
	{
		if (str[i] == '$')
		{
			// len_var is already defined, no need to redefine it
			if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			{
				while (str[i + len_var] && (ft_isalnum(str[i + len_var]) || str[i + len_var] == '_'))
					len_var++;
				temp = ft_substr_g_c(str + i + 1, 0, len_var - 1, &(ma->first_node));
				env_value = get_env(temp, ma->env->var);
				if (env_value)
				{
					result = ft_strjoin_g_c(result, env_value, &(ma->first_node));
					len_after = 0;
					while (str[i + len_var + len_after] && !ft_strchr(" ><&()|$", str[i + len_var + len_after]))
						len_after++;
					ad_word = ft_substr_g_c(str, i + len_var, len_after, &(ma->first_node));
					result = ft_strjoin_g_c(result, ad_word, &(ma->first_node));
				}
			}
			i += len_var;
		}
		else
		{
			append_char(str[i], &result, ma);
			i++;
		}
	}
	return (result);
} */

void	generate_regular_tkns(const char **s, char ***split, int *i,
		t_ma *ma)
{
	int		word_length;
	char	*temp;
	char	*trimmed;
	char	*result;
	int		len_var;
	char	*env_value;
	int		len_after;
	char	*ad_word;

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
		else if (!ft_strchr("' ><&()|$", (*s)[word_length]))
			word_length++;
		else
			break;
	}
	temp = ft_substr_g_c(*s, 0, word_length, &(ma->first_node));
	// printf("temp: %s\n", temp);
	if (ft_strchr(temp, '=') && ft_strchr(temp, '"') && ft_strchr(temp, '$'))
	{
	    result = ft_strdup_g_c("", &(ma->first_node));
	    int i = 0;
	    int len_var;
	
	    // Copia la parte antes del '='
	    while (temp[i] != '=')
	        append_char(temp[i++], &result, ma);
	
	    // Procesa el resto de la cadena
	    while (temp[i])
	    {
	        if (temp[i] == '$')
	        {
	            len_var = 1;
	            if (ft_isalnum(temp[i + 1]) || temp[i + 1] == '_')
	            {
	                while (temp[i + len_var] && (ft_isalnum(temp[i + len_var]) || temp[i + len_var] == '_'))
	                    len_var++;
	
	                // Extrae el nombre de la variable de entorno
	                char *var_name = ft_substr_g_c(temp, i + 1, len_var - 1, &(ma->first_node));
	
	                // Obtiene el valor de la variable de entorno
	                env_value = get_env(var_name, ma->env->var);
	
	                // Si existe la variable de entorno, concatenarla
	                if (env_value)
	                {
	                    result = ft_strjoin_g_c(result, env_value, &(ma->first_node));
	                }
	
	                // Avanza el índice 'i' para saltar la variable de entorno ya procesada
	                i += len_var;
	            }
	        }
	        else
	        {
	            // Si no es una variable de entorno, simplemente agregar el carácter
	            append_char(temp[i], &result, ma);
	            i++;
	        }
	    }
	    // printf("result: %s\n", result);    
	}
	else
	{
		result = temp;
		len_var = 1;
		if (((*s)[word_length] == '$') && (ft_isalnum((*s)[word_length + 1]) || (*s)[word_length + 1] == '_'))
		{
			while ((*s)[word_length + len_var] && (ft_isalnum((*s)[word_length + len_var]) || (*s)[word_length + len_var] == '_'))
    	        len_var++;
			temp = ft_substr_g_c(*s + word_length + 1, 0, len_var - 1, &(ma->first_node));
			env_value = get_env(temp, ma->env->var);
			if (env_value)
			{
				result = ft_strjoin_g_c(result, env_value, &(ma->first_node));
				len_after = 0;
				while ((*s)[word_length + len_var + len_after] && !ft_strchr(" ><&()|$", (*s)[word_length + len_var + len_after]))
    	                len_after++;
				ad_word = ft_substr_g_c(*s, word_length + len_var, len_after, &(ma->first_node));
				result = ft_strjoin_g_c(result, ad_word, &(ma->first_node));
			}
		}
	}
	// result = expand_vars(temp, ma);
	trimmed = ft_strremove_quotes(result, &(ma->first_node));
	// printf("trimmed: %s\n", trimmed);0
	(*split)[(*i)++] = trimmed;
	*s += word_length;
}

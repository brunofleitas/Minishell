[1mdiff --git a/5-split_generator.c b/5-split_generator.c[m
[1mnew file mode 100644[m
[1mindex 0000000..d47e917[m
[1m--- /dev/null[m
[1m+++ b/5-split_generator.c[m
[36m@@ -0,0 +1,296 @@[m
[32m+[m[32m/* ************************************************************************** */[m
[32m+[m[32m/*                                                                            */[m
[32m+[m[32m/*                                                        :::      ::::::::   */[m
[32m+[m[32m/*   5-split_generator.c                                :+:      :+:    :+:   */[m
[32m+[m[32m/*                                                    +:+ +:+         +:+     */[m
[32m+[m[32m/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */[m
[32m+[m[32m/*                                                +#+#+#+#+#+   +#+           */[m
[32m+[m[32m/*   Created: 2024/07/11 19:14:08 by bfleitas          #+#    #+#             */[m
[32m+[m[32m/*   Updated: 2024/08/20 12:54:13 by bfleitas         ###   ########.fr       */[m
[32m+[m[32m/*                                                                            */[m
[32m+[m[32m/* ************************************************************************** */[m
[32m+[m
[32m+[m[32m#include "minishell.h"[m
[32m+[m
[32m+[m[32mstatic char	*get_env(char *name, char **env)[m
[32m+[m[32m{[m
[32m+[m	[32mint		i;[m
[32m+[m	[32mint		name_len;[m
[32m+[m
[32m+[m	[32mif (!name || !env)[m
[32m+[m		[32mreturn (NULL);[m
[32m+[m	[32mname_len = strlen(name);[m
[32m+[m	[32mi = 0;[m
[32m+[m	[32mwhile (env[i])[m
[32m+[m	[32m{[m
[32m+[m		[32mif (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')[m
[32m+[m			[32mreturn (&env[i][name_len + 1]);[m
[32m+[m		[32mi++;[m
[32m+[m	[32m}[m
[32m+[m	[32mreturn (NULL);[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mstatic void	handle_env_var(const char **s, char **result, int *result_len, t_ma *ma)[m
[32m+[m[32m{[m
[32m+[m	[32mchar	var_name[1024];[m
[32m+[m	[32mint		var_name_len;[m
[32m+[m	[32mchar	*env_value;[m
[32m+[m
[32m+[m	[32mvar_name_len = 0;[m
[32m+[m	[32m(*s)++;[m
[32m+[m	[32mwhile (ft_isalnum(**s) || **s == '_')[m
[32m+[m		[32mvar_name[var_name_len++] = *(*s)++;[m
[32m+[m	[32mvar_name[var_name_len] = '\0';[m
[32m+[m	[32menv_value = get_env(var_name, (ma->env->var));[m
[32m+[m	[32mif (env_value)[m
[32m+[m	[32m{[m
[32m+[m		[32m*result = ft_realloc_g_c(&(ma->first_node), *result, (*result_len + strlen(env_value) + 1));[m
[32m+[m		[32mif (*result)[m
[32m+[m		[32m{[m
[32m+[m			[32mstrcpy(*result + *result_len, env_value);[m
[32m+[m			[32m*result_len += strlen(env_value);[m
[32m+[m		[32m}[m
[32m+[m	[32m}[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mstatic void	append_char(const char *s, char **result, int *result_len, t_ma *ma)[m
[32m+[m[32m{[m
[32m+[m	[32m*result = ft_realloc_g_c(&(ma->first_node), *result, *result_len + 2);[m
[32m+[m	[32mif (*result)[m
[32m+[m	[32m{[m
[32m+[m		[32m(*result)[(*result_len)++] = *s;[m
[32m+[m		[32m(*result)[*result_len] = '\0';[m
[32m+[m	[32m}[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mstatic void	generate_quotes(const char **s, char ***split, int *i, t_ma *ma)[m
[32m+[m[32m{[m
[32m+[m	[32mchar	quote;[m
[32m+[m	[32mchar	*result;[m
[32m+[m	[32mint		result_len;[m
[32m+[m	[32mchar	*exit_value;[m
[32m+[m
[32m+[m	[32mquote = **s;[m
[32m+[m	[32m(*s)++;[m
[32m+[m	[32mresult = ft_strdup_g_c("", &(ma->first_node));[m
[32m+[m	[32mresult_len = 0;[m
[32m+[m	[32mappend_char(&quote, &result, &result_len, ma);[m
[32m+[m	[32mwhile (**s && **s != quote)[m
[32m+[m	[32m{[m
[32m+[m		[32mif (quote == '"' && **s == '$' && ft_isalnum(*(*s + 1)))[m
[32m+[m			[32mhandle_env_var(s, &result, &result_len, ma);[m
[32m+[m		[32melse if (quote == '"' && **s == '$' && (*(*s + 1) == '?'))[m
[32m+[m		[32m{[m
[32m+[m			[32mexit_value = ft_substr_g_c(ft_itoa_g_c(ma->last_exit_status, &(ma->first_node)), 0, ft_strlen(ft_itoa_g_c(ma->last_exit_status, &(ma->first_node))), &(ma->first_node));[m
[32m+[m			[32mwhile (*exit_value)[m
[32m+[m				[32mappend_char(exit_value++, &result, &result_len, ma);[m
[32m+[m			[32m(*s) += 2;[m
[32m+[m		[32m}[m
[32m+[m		[32melse[m
[32m+[m		[32m{[m
[32m+[m			[32mappend_char(*s, &result, &result_len, ma);[m
[32m+[m			[32m(*s)++;[m
[32m+[m		[32m}[m
[32m+[m	[32m}[m
[32m+[m	[32mappend_char(&quote, &result, &result_len, ma);[m
[32m+[m	[32m(*split)[(*i)++] = result;[m
[32m+[m	[32mif (**s == quote)[m
[32m+[m		[32m(*s)++;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m/*[m
[32m+[m[32m  Parameters:[m
[32m+[m[32m    s: Pointer to the input string.[m
[32m+[m[32m    split: Pointer to the array of pointers to strings (tkns).[m
[32m+[m[32m    i: Pointer to an integer indicating the current index in the tkns array.[m
[32m+[m[32m  Description:[m
[32m+[m[32m    Extracts and stores a double operator (e.g., '>>', '<<', '&&', '||') from[m[41m [m
[32m+[m	[32mthe input string into the tkns array. Advances the input string by 2[m[41m [m
[32m+[m	[32mpositions to skip the operator.[m
[32m+[m[32m*/[m
[32m+[m[32mstatic void	generate_double_operators(const char **s, char ***split, int *i, \[m
[32m+[m															[32mt_ma *ma)[m
[32m+[m[32m{[m
[32m+[m	[32m(*split)[(*i)++] = ft_substr_g_c(*s, 0, 2, &(ma->first_node));[m
[32m+[m	[32m*s += 2;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m
[32m+[m[32m/**[m
[32m+[m[32m * Generates single operators and special characters from the input string (including '$?')[m[41m [m
[32m+[m[32m * from the input string into the tkns array. The length of the substring[m[41m [m
[32m+[m[32m * depends on the specific operator or special character.[m
[32m+[m[32m * Advances the input string by the length of the extracted substring.[m[41m [m
[32m+[m[32m * @param s The input string.[m
[32m+[m[32m * @param split The array to store the generated strings.[m
[32m+[m[32m * @param i The index of the current element in the split array.[m
[32m+[m[32m * @param ma The main structure containing relevant data.[m
[32m+[m[32m */[m
[32m+[m[32mstatic void	generate_single_operators_and_specials(const char **s,[m
[32m+[m		[32mchar ***split, int *i, t_ma *ma)[m
[32m+[m[32m{[m
[32m+[m	[32mint	len;[m
[32m+[m	[32mchar	*temp;[m
[32m+[m	[32mchar	*env_value;[m
[32m+[m
[32m+[m	[32mlen = 1;[m
[32m+[m	[32mif (**s == '$' && *(*s + 1) == '?')[m
[32m+[m	[32m{[m
[32m+[m		[32m(*split)[(*i)++] = ft_substr_g_c(ft_itoa_g_c(ma->last_exit_status, &(ma->first_node)), 0, ft_strlen(ft_itoa_g_c(ma->last_exit_status, &(ma->first_node))), &(ma->first_node));[m
[32m+[m		[32m(*s) += 1;[m
[32m+[m	[32m}[m
[32m+[m	[32melse if (**s == '$' && ft_isalnum(*(*s + 1)))[m
[32m+[m	[32m{[m
[32m+[m		[32mwhile ((*s)[len] && (ft_isalnum((*s)[len]) || (*s)[len] == '_'))[m
[32m+[m			[32mlen++;[m
[32m+[m		[32mtemp = ft_substr_g_c(*s + 1, 0, len - 1, &(ma->first_node));[m
[32m+[m		[32menv_value = get_env(temp, ma->env->var);[m
[32m+[m		[32mif (env_value)[m
[32m+[m			[32m(*split)[(*i)++] = ft_strdup_g_c(env_value, &(ma->first_node));[m
[32m+[m		[32melse[m
[32m+[m			[32m(*split)[(*i)++] = ft_strdup_g_c("", &(ma->first_node));[m
[32m+[m	[32m}[m
[32m+[m	[32melse[m
[32m+[m	[32m{[m
[32m+[m		[32m(*split)[(*i)++] = ft_substr_g_c(*s, 0, 1, &(ma->first_node));[m
[32m+[m	[32m}[m
[32m+[m	[32m*s += len;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mchar *ft_strremove_char(const char *str, char char_to_remove, t_ntc **first_node)[m
[32m+[m[32m{[m
[32m+[m[32m    char *result;[m
[32m+[m[32m    int i;[m
[32m+[m[32m    int j;[m
[32m+[m
[32m+[m[32m    if (!str) {[m
[32m+[m[32m        return NULL;[m
[32m+[m[32m    }[m
[32m+[m[32m    result = g_c(first_node, sizeof(char) * (strlen(str) + 1))->data;[m
[32m+[m[32m    if (!result) {[m
[32m+[m[32m        return NULL;[m
[32m+[m[32m    }[m
[32m+[m[32m    i = 0;[m
[32m+[m[32m    j = 0;[m
[32m+[m[32m    while (str[i] != '\0') {[m
[32m+[m[32m        if (str[i] != char_to_remove) {[m
[32m+[m[32m            result[j++] = str[i];[m
[32m+[m[32m        }[m
[32m+[m[32m        i++;[m
[32m+[m[32m    }[m
[32m+[m[32m    result[j] = '\0';[m
[32m+[m[32m    return result;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m/*[m
[32m+[m[32m  Parameters:[m
[32m+[m[32m    s: Pointer to the input string.[m
[32m+[m[32m    split: Pointer to the array of pointers to strings (tkns).[m
[32m+[m[32m    i: Pointer to an integer indicating the current index in the tkns array.[m
[32m+[m[32m  Description:[m
[32m+[m[32m    Extracts and stores a regular token (any sequence of characters not[m[41m [m
[32m+[m	[32mmatching the specified operators or special characters) from the input[m[41m [m
[32m+[m	[32mstring into the tkns array. Calculates the length of the token by finding[m[41m [m
[32m+[m	[32mthe first occurrence of an operator or special character. Advances the[m[41m [m
[32m+[m	[32minput string by the length of the extracted token.[m
[32m+[m[32m*/[m
[32m+[m[32mstatic void	generate_regular_tkns(const char **s, char ***split, int *i, \[m
[32m+[m																[32mt_ma *ma)[m
[32m+[m[32m{[m
[32m+[m	[32mint	word_length;[m
[32m+[m	[32mchar	*temp;[m
[32m+[m	[32mchar	*trimmed;[m
[32m+[m	[32mchar *result;[m
[32m+[m
[32m+[m	[32mword_length = 0;[m
[32m+[m	[32mwhile ((*s)[word_length] && !strchr(" ><&()|$", (*s)[word_length]))[m
[32m+[m	[32m{[m
[32m+[m		[32mif (ft_isdigit((*s)[word_length]) && ((*s)[word_length + 1] && (*s)[word_length + 1] == '>') && ((*s)[word_length + 2] && (*s)[word_length + 2] == '>'))[m
[32m+[m			[32mbreak ;[m
[32m+[m		[32melse if (ft_isdigit((*s)[word_length]) && ((*s)[word_length + 1] && (*s)[word_length + 1] == '>'))[m
[32m+[m			[32mbreak ;[m
[32m+[m		[32melse[m
[32m+[m			[32mword_length++;[m
[32m+[m	[32m}[m
[32m+[m	[32mtemp = ft_substr_g_c(*s, 0, word_length, &(ma->first_node));[m
[32m+[m	[32mtrimmed = ft_strremove_char(temp, '\'', &(ma->first_node));[m
[32m+[m	[32mresult = ft_strremove_char(trimmed, '\"', &(ma->first_node));[m
[32m+[m	[32mresult = ft_strtrim(result, " ", &(ma->first_node));[m
[32m+[m	[32m(*split)[(*i)++] = result;[m
[32m+[m	[32m*s += word_length;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32m// static void handle_redirection(const char **s, char ***split, int *i, t_ntc **first_node)[m
[32m+[m[32m// {[m
[32m+[m[32m//     if (ft_isdigit((*s)[0]) && (((*s)[1] == '>') || ((*s)[1] == '>' && (*s)[2] == '>')))[m
[32m+[m[32m// 	{[m
[32m+[m[32m//         char *token;[m
[32m+[m[32m//         int length;[m
[32m+[m[41m        [m
[32m+[m[32m//         if ((*s)[1] == '>' && (*s)[2] == '>')[m
[32m+[m[32m//             length = 3;[m
[32m+[m[32m//         else[m
[32m+[m[32m//             length = 2;[m
[32m+[m[32m//         token = ft_substr_g_c(*s, 0, length, first_node);[m
[32m+[m[32m//         (*split)[(*i)++] = token;[m
[32m+[m[32m//         *s += length;[m
[32m+[m[32m//     }[m
[32m+[m[32m// }[m
[32m+[m
[32m+[m[32m/*[m
[32m+[m[32m  Parameters:[m
[32m+[m	[32ms: Input string to be split into tkns.[m
[32m+[m	[32mc: Character used to determine token boundaries.[m
[32m+[m[32m  Return value:[m
[32m+[m	[32mA pointer to an array of strings, each representing a token from the input[m
[32m+[m	[32mstring.[m
[32m+[m	[32mReturns NULL if the input string or the allocated memory cannot be processed[m
[32m+[m[32m  Description:[m
[32m+[m	[32mSplits the input string into tkns based on the specified delimiter[m
[32m+[m	[32mcharacter.[m
[32m+[m	[32mHandles various cases including quotes, double operators, single operators,[m
[32m+[m	[32mand regular tkns. Allocates memory for the resulting array of tkns and[m
[32m+[m	[32minitializes it accordingly. The last element of the array is set to NULL[m
[32m+[m	[32mto indicate the end.[m
[32m+[m[32m*/[m
[32m+[m[32m/**[m
[32m+[m[32m * Splits a string into tokens based on a given delimiter.[m
[32m+[m[32m *[m
[32m+[m[32m * @param c The delimiter character.[m
[32m+[m[32m * @param ma The memory allocator structure.[m
[32m+[m[32m * @return An array of strings representing the tokens.[m
[32m+[m[32m */[m
[32m+[m[32mchar **ft_split_tkns(char c, t_ma *ma)[m
[32m+[m[32m{[m
[32m+[m	[32mchar **split;[m
[32m+[m	[32mint i;[m
[32m+[m	[32mconst char *s;[m
[32m+[m
[32m+[m	[32ms = (const char*)ma->input;[m
[32m+[m	[32mi = 0;[m
[32m+[m	[32m//printf("%i\n", count_tks(s, c));[m
[32m+[m	[32msplit = g_c(&(ma->first_node), (count_tks(s, c) + 1) * sizeof(char *))->data;[m
[32m+[m	[32mif (!s || !split)[m
[32m+[m		[32mreturn (NULL);[m
[32m+[m	[32mwhile (*s)[m
[32m+[m	[32m{[m
[32m+[m		[32mif (*s == c)[m
[32m+[m			[32ms++;[m
[32m+[m		[32m// else if (ft_isdigit(*s))[m
[32m+[m[32m        //     handle_redirection(&s, &split, &i, first_node);[m
[32m+[m		[32melse if (*s == '"' || *s == '\'')[m
[32m+[m			[32mgenerate_quotes(&s, &split, &i, ma);[m
[32m+[m		[32melse if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s[m
[32m+[m					[32m+ 1) == '<') || (*s == '&' && *(s + 1) == '&') || (*s == '|'[m
[32m+[m				[32m&& *(s + 1) == '|'))[m
[32m+[m			[32mgenerate_double_operators(&s, &split, &i, ma);[m
[32m+[m		[32melse if (*s == '>' || *s == '<' || *s == '(' || *s == ')' || *s == '|'[m
[32m+[m			[32m|| (*s == '$' && *(s + 1) == '?') || *s == '$')[m
[32m+[m			[32mgenerate_single_operators_and_specials(&s, &split, &i, ma);[m[41m			[m
[32m+[m		[32melse[m
[32m+[m			[32mgenerate_regular_tkns(&s, &split, &i, ma);[m
[32m+[m	[32m}[m
[32m+[m	[32msplit[i] = NULL;[m
[32m+[m	[32mreturn (split);[m
[32m+[m[32m}[m
[32m+[m[32m// f_node is an alias for first_node but I had to shorten it otherwise the funtion would have been more than 25 lines long.[m

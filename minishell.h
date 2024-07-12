

#ifndef MINISHELL_H
# define MINISHELL_H

#include "ft_printf.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
  t_token_type: An enumeration representing different types of tokens encountered
  in a minishell environment.
  Values:
	TOKEN_COMMAND_ECHO: Represents an echo command token.
	TOKEN_COMMAND_CD: Represents a change directory command token.
	TOKEN_COMMAND_PWD: Represents a print working directory command token.
	TOKEN_COMMAND_EXPORT: Represents an export command token.
	TOKEN_COMMAND_UNSET: Represents an unset command token.
	TOKEN_COMMAND_ENV: Represents an environment variable command token.
	TOKEN_REDIRECT_IN: Represents an input redirection token.
	TOKEN_REDIRECT_OUT: Represents an output redirection token.
	TOKEN_REDIRECT_APPEND: Represents an append redirection token.
	TOKEN_HERE_DOCUMENT: Represents a here document token.
	TOKEN_PIPE: Represents a pipe token.
	TOKEN_AND: Represents an AND logical operator token.
	TOKEN_OR: Represents an OR logical operator token.
	TOKEN_VARIABLE: Represents a variable token.
	TOKEN_VARIABLE_EXIT: Represents a variable exit status token.
	TOKEN_STRING_SINGLE: Represents a single-quoted string token.
	TOKEN_STRING_DOUBLE: Represents a double-quoted string token.
	TOKEN_ARGUMENT: Represents a general argument token.
	TOKEN_ERROR: Represents an error token.
*/
typedef enum e_token_type
{
	TOKEN_ERROR ,
	TOKEN_COMMAND_ECHO,
	TOKEN_COMMAND_CD,
	TOKEN_COMMAND_PWD,
	TOKEN_COMMAND_EXPORT,
	TOKEN_COMMAND_UNSET,
	TOKEN_COMMAND_ENV,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HERE_DOCUMENT,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_VARIABLE,
	TOKEN_VARIABLE_EXIT,
	TOKEN_STRING_SINGLE,
	TOKEN_STRING_DOUBLE,
	TOKEN_ARGUMENT,
}				t_token_type;

/* ************************************************************************** */
/*                           STRUCTURE DEFINITIONS                            */                           
/* ************************************************************************** */
typedef struct s_word
{
	t_token_type	key;
	char		*value;
}				t_word;

/* ************************  GARBAGE COLLECTOR NODE  ************************ */
typedef struct s_ntc
{
	void			*data;
	struct s_ntc	*next;
	struct s_ntc	*prev;

}					t_ntc;
// ntc = node to clean


/* ************************************************************************** */
/*                                   FUNCTIONS                                */
/* ************************************************************************** */
void				lexer(char *input);
int					count_words_tokens(char const *s, char c);
char				**ft_split_tokens(char const *s, char c);
t_token_type		clasify_token(char *value);
t_ntc				*garbage_collector(t_ntc **first_node, size_t size_of);

#endif